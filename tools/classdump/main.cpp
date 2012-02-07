#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdarg.h>
#include <algorithm>
#include <iostream>

class DecodeException : public std::exception {
public:
	DecodeException(const std::string& what)
		: mWhat(what)
	{
	}

	DecodeException(char* format, ...){
		char buffer[256];

		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, 256, format, args);
		va_end(args);

		mWhat = buffer;
	}

	virtual const char* what() const throw() {
		return mWhat.c_str();
	}

private:
	std::string mWhat;
};

struct Variable {
	std::string mName;
	std::string mType;
	std::string mValue;
};

struct Class {
	std::string mName;
	std::string mFullName;
	std::vector<Variable*> mVariables;
};

struct Argument {
	std::string mName;
	std::string mType;
};

struct Function {
	std::string mName;
	std::vector<Argument*> mArguments;
};

struct Service {
	std::string mName;
	std::string mFullName;
	std::vector<Function*> mFunctions;
};

struct Package {
	std::string mName;
	std::vector<std::string> mImports;
	std::vector<Class*> mClasses;
	std::vector<Service*> mServices;
};

std::vector<Package*> gPackages;

void readToken(std::stringstream& fh, const std::string& token){
	std::string _tmp;
	fh >> _tmp;
	if(_tmp.compare(token))
		throw new DecodeException("Expected token %s, found %s", token.c_str(), _tmp.c_str());
}

Service* parseService(std::stringstream& fh){
	std::string token;
	Service* svc = new Service();

	fh >> svc->mName;
	svc->mFullName = svc->mName;
	while(token.compare("{"))
		fh >> token;

	readToken(fh, "public");
	readToken(fh, "function");
	fh >> token;

	fh >> token;
	while(true){
		if(token.compare("function"))
			break;

		Function* fnc = new Function();
		fh >> token;
		fnc->mName = token.substr(0, token.find('('));
		token = token.substr(token.find('(') + 1);
		
		while(true){
			if(token.compare(":") == 0)
				break;

			Argument* arg = new Argument();
			arg->mName = token.substr(0, token.find(':'));
			arg->mType = token.substr(token.find(':') + 1);
			
			int pos = arg->mType.find(',');
			if(pos != std::string::npos)
				arg->mType.erase(pos, 1);
			
			pos = arg->mType.find(')');
			if(pos != std::string::npos)
				arg->mType.erase(pos, 1);

			fnc->mArguments.push_back(arg);

			fh >> token;
		}

		svc->mFunctions.push_back(fnc);
		readToken(fh, "void;");
		
		fh >> token;
	}

	return svc;
}

Class* parseClass(std::stringstream& fh){
	std::string token;
	Class* cls = new Class();
	
	fh >> cls->mName;
	cls->mFullName = cls->mName;
	while(token.compare("{"))
		fh >> token;
	
	fh >> token;
	while(true){
		if(token.compare("public") && token.compare("private"))
			break;

		bool isPrivate = token.compare("private") == 0;

		fh >> token;
		if(token.compare("var"))
			break;

		Variable* var = new Variable();

		fh >> var->mName;
		if(isPrivate){
			if(var->mName[0] == '_'){
				int pos = var->mName.find_first_not_of("0123456789_");
				var->mName = var->mName.substr(pos);
			}
		}

		int pos = var->mName.find(';');
		if(pos != std::string::npos)
			var->mName.erase(pos, 1);

		var->mType = var->mName.substr(var->mName.find(':') + 1);
		var->mName = var->mName.substr(0, var->mName.find(':'));

		if(var->mType.compare("ArrayCollection") == 0)
			var->mType = "amf::Array";
		else if(var->mType.compare("Date") == 0)
			var->mType = "amf::Date";

		fh >> token;
		if(token.compare("=") == 0){
			fh >> var->mValue;
			fh >> token;

			int pos = var->mValue.find(';');
			if(pos != std::string::npos)
				var->mValue.erase(pos, 1);
		}

		cls->mVariables.push_back(var);
	}

	int scopes = 0;
	do {
		fh >> token;

		if(token.find("{") != std::string::npos)
			++scopes;
		else if(token.find("}") != std::string::npos)
			--scopes;
	}while(scopes >= 0);

	return cls;
}

Package* parsePackage(std::stringstream& fh){
	std::string token;

	readToken(fh, "package");
	fh >> token;
	readToken(fh, "{");
	
	Package* pkg = new Package();
	pkg->mName = token;
	gPackages.push_back(pkg);

	while(true){
		fh >> token;
		if(token.compare("import") == 0){
			fh >> token;

			if(std::find(pkg->mImports.begin(), pkg->mImports.end(), token) == pkg->mImports.end())
				pkg->mImports.push_back(token);
		}else if(token.compare("public") == 0){
			fh >> token;
			if(token.compare("class") == 0){
				Class* cls = parseClass(fh);
				cls->mFullName = pkg->mName + "." + cls->mFullName;
				pkg->mClasses.push_back(cls);
			}else if(token.compare("interface") == 0){
				Service* svc = parseService(fh);
				svc->mFullName = pkg->mName + "." + svc->mFullName;
				pkg->mServices.push_back(svc);
			}
		}else
			break;
	}

	return pkg;
}

std::string indent;

void addPackageHeader(Package* pkg, std::ostream& strm){
	indent = std::string();

	strm << "#pragma once" << std::endl << std::endl;

	if(pkg->mClasses.size())
		strm << "#include \"amf/variant.h\"" << std::endl;

	if(pkg->mServices.size())
		strm << "#include \"flex/services.h\"" << std::endl;
	
	for(auto itr = pkg->mImports.begin(); itr != pkg->mImports.end(); ++itr){
		std::string imp = *itr;
		if(imp.find("com.riotgames") != 0) continue;
		
		int pos = imp.find(".*;");
		if(pos != std::string::npos)
			imp.erase(pos, 3);

		imp = imp.substr(imp.find_last_of('.') + 1);
		strm << "#include \"" << imp << ".h\"" << std::endl;
	}

	strm << std::endl;

	int pos = 0;
	while(true){
		int next = pkg->mName.find('.', pos);
		std::string nspace = pkg->mName.substr(pos, next - pos);
		if(nspace.compare("com") != 0){
			strm << indent << "namespace " << nspace << " {" << std::endl;
			indent.append("\t");
		}

		if(next == std::string::npos)
			break;

		pos = next + 1;
	}

	for(auto itr = pkg->mImports.begin(); itr != pkg->mImports.end(); ++itr){
		std::string imp = *itr;
		if(imp.find("com.riotgames") != 0) continue;
		
		for(int pos = imp.find("."); pos != std::string::npos; pos = imp.find("."))
			imp = imp.replace(pos, 1, "::");
		
		for(int pos = imp.find("::*"); pos != std::string::npos; pos = imp.find("::*"))
			imp = imp.erase(pos, 3);
		
		imp = imp.erase(0, 5);
		strm << indent << "using namespace " << imp << std::endl;
	}

	if(pkg->mImports.size())
		strm << std::endl;
}

void addPackageFooter(Package* pkg, std::ostream& strm){
	while(indent.length()){
		indent.erase(0, 1);
		strm << indent << "};" << std::endl;
	}
}
#include <windows.h>
void outputPackage(Package* pkg){
	std::string base_dir = pkg->mName + "/";
	
	for(int pos = base_dir.find('.'); pos != std::string::npos; pos = base_dir.find('.'))
		base_dir.replace(pos, 1, "/");

	system((std::string("mkdir \"") + base_dir + "\"").c_str());

	for(auto itr = pkg->mClasses.begin(); itr != pkg->mClasses.end(); ++itr){
		std::stringstream strm;
		addPackageHeader(pkg, strm);

		Class* cls = *itr;
		strm << indent << "class " << cls->mName << " : public amf::Object {" << std::endl;
		strm << indent << "public:" << std::endl;
		indent.append("\t");

		strm << indent << cls->mName << "(){" << std::endl;
		indent.append("\t");
		
		strm << indent << "setName(\"" << cls->mFullName << "\");" << std::endl << std::endl;

		for(auto jtr = cls->mVariables.begin(); jtr != cls->mVariables.end(); ++jtr){
			Variable* var = *jtr;
			strm << indent << "set(\"" << var->mName << "\", ";

			if(var->mType.compare("amf::Array") == 0){
				strm << "new amf::Array()";
			}else if(var->mValue.length() == 0 || var->mValue.compare("null") == 0){
				strm << "(amf::Null*)nullptr";
			}else{
				strm << var->mValue;
			}

			strm << ");" << std::endl;
		}

		indent.erase(0, 1);
		strm << indent << "}" << std::endl;

		//now get
		for(auto jtr = cls->mVariables.begin(); jtr != cls->mVariables.end(); ++jtr){
			Variable* var = *jtr;
			
			strm << std::endl << indent;
			if(var->mType.compare("String") == 0){
				strm << "std::string";
			}else if(var->mType.compare("Number") == 0){
				strm << "double";
			}else if(var->mType.compare("int") == 0){
				strm << "int";
			}else if(var->mType.compare("Boolean") == 0){
				strm << "bool";
			}else{
				strm << "const amf::Reference<" << var->mType << ">";
			}

			std::string name = var->mName;
			if(name[0] >= 'a' && name[0] <= 'z')
				name[0] = (name[0] - 'a') + 'A';

			strm << " get" << name << "() const {" << std::endl;
			indent.append("\t");
			
			if(var->mType.compare("String") == 0
			 || var->mType.compare("Number") == 0
			 || var->mType.compare("int") == 0
			 || var->mType.compare("Boolean") == 0
			 || var->mType.compare("amf::Array") == 0
			 || var->mType.compare("amf::Date") == 0){
				strm << indent << "return get(\"" << var->mName << "\");" << std::endl;
			}else{
				strm << indent << "return get(\"" << var->mName << "\").toObject();" << std::endl;
			}
			
			indent.erase(0, 1);
			strm << indent << "}" << std::endl;
		}

		//set
		for(auto jtr = cls->mVariables.begin(); jtr != cls->mVariables.end(); ++jtr){
			Variable* var = *jtr;
			
			std::string name = var->mName;
			if(name[0] >= 'a' && name[0] <= 'z')
				name[0] = (name[0] - 'a') + 'A';

			strm << std::endl << indent << "void set" << name << "(";

			if(var->mType.compare("String") == 0){
				strm << "const std::string& value";
			}else if(var->mType.compare("Number") == 0){
				strm << "double value";
			}else if(var->mType.compare("int") == 0){
				strm << "int value";
			}else if(var->mType.compare("Boolean") == 0){
				strm << "bool value";
			}else{
				strm << var->mType << "* value";
			}
				
			strm << "){" << std::endl;
			indent.append("\t");
			strm << indent << "get(\"" << var->mName << "\") = value;" << std::endl;
			indent.erase(0, 1);
			strm << indent << "}" << std::endl;
		}

		indent.erase(0, 1);
		strm << indent << "};" << std::endl;

		addPackageFooter(pkg, strm);

		std::string filename = cls->mName;
		std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

		std::ofstream out(base_dir + filename + ".h");
		out << strm.rdbuf();
		out.close();
	}

	for(auto itr = pkg->mServices.begin(); itr != pkg->mServices.end(); ++itr){
		std::stringstream strm;
		addPackageHeader(pkg, strm);

		Service* svc = *itr;
		strm << indent << "class " << svc->mName << " : private flex::messaging::services::Service {" << std::endl;
		strm << indent << "public:" << std::endl;

		indent.append("\t");

		std::string name = svc->mName;
		if(name[0] >= 'A' && name[0] <= 'Z')
			name[0] = (name[0] - 'A') + 'a';

		strm << indent << svc->mName << "()" << std::endl;
		strm << indent << "\t: flex::messaging::services::Service(\"" << name << "\")" << std::endl;
		strm << indent << "{" << std::endl;
		strm << indent << "}" << std::endl;

		strm << std::endl;
		
		for(auto jtr = svc->mFunctions.begin(); jtr != svc->mFunctions.end(); ++jtr){
			if(jtr != svc->mFunctions.begin())
				strm << std::endl;

			Function* func = *jtr;
			strm << indent << "void " << func->mName << "(";

			bool putArg = false;
			for(auto ktr = func->mArguments.begin(); ktr != func->mArguments.end(); ++ktr){
				Argument* arg = *ktr;
				
				if(arg->mType.compare("Function") == 0)
					continue;

				if(putArg)
					strm << ", ";

				if(arg->mType.compare("String") == 0){
					strm << "const std::string& ";
				}else if(arg->mType.compare("Number") == 0){
					strm << "double ";
				}else if(arg->mType.compare("int") == 0){
					strm << "int ";
				}else if(arg->mType.compare("Boolean") == 0){
					strm << "bool ";
				}else if(arg->mType.compare("Array") == 0){
					strm << "amf::Array* ";
				}else if(arg->mType.compare("Object") == 0){
					strm << "amf::Object* ";
				}else if(arg->mType.compare("Date") == 0){
					strm << "amf::Date* ";
				}else{
					strm << arg->mType << "* ";
				}

				strm << arg->mName;
				putArg = true;
			}
			
			if(putArg)
				strm << ", ";

			strm << "const rtmp::CommandCallback& callback){" << std::endl;

			strm << indent << "\tinvoke(\"" << func->mName << "\", callback";
			
			for(auto ktr = func->mArguments.begin(); ktr != func->mArguments.end(); ++ktr){
				Argument* arg = *ktr;
				
				if(arg->mType.compare("Function") == 0)
					continue;

				strm << ", " << arg->mName;
			}

			strm << ");" << std::endl;
			strm << indent << "}" << std::endl;
		}

		indent.erase(0, 1);
		strm << indent << "};" << std::endl;

		addPackageFooter(pkg, strm);

		std::string filename = svc->mName;
		std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

		std::ofstream out(base_dir + filename + ".h");
		out << strm.rdbuf();
		out.close();
	}
}

int main(int argc, char** argv){
	while(true){
		std::string source;
		std::getline(std::cin, source);
		if(source.length() == 0)
			break;

		std::ifstream in(source);
		if(in.is_open()){
			std::stringstream fh;
			fh << in.rdbuf();

			if(fh.peek() == 0xEF)
				fh.seekg(3);

			in.close();

			parsePackage(fh);
		}
	}
	
	for(auto itr = gPackages.begin(); itr != gPackages.end(); ++itr){
		Package* pkg = *itr;
		outputPackage(pkg);
	}

	return 0;
}
