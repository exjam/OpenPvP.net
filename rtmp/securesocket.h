#pragma once

#include "socket.h"
#include <openssl/ssl.h>

class SecureSocket : public Socket {
public:
	SecureSocket(){
		SSL_library_init();
		SSL_load_error_strings();
		OpenSSL_add_all_digests();
	
		mContext = SSL_CTX_new(SSLv23_method());
		SSL_CTX_set_options(mContext, SSL_OP_ALL);
		SSL_CTX_set_default_verify_paths(mContext);

		mSSL = SSL_new(mContext);
	}

	virtual ~SecureSocket(){
		SSL_free(mSSL);
		SSL_CTX_free(mContext);
	}
	
	virtual bool connect(const char* host, int port){
		if(!connectBlocking(host, port))
			return false;

		SSL_set_fd(mSSL, mSocket);
		mResult = SSL_connect(mSSL);
		if(mResult <= 0)
			return false;

		u_long iMode = 1;
		ioctlsocket(mSocket, FIONBIO, &iMode);

		return true;
	}

	virtual bool disconnect(){
		SSL_shutdown(mSSL);
		return Socket::disconnect();
	}

	virtual int read(uint8* data, uint32 length){
		mResult = SSL_read(mSSL, data, length);

		if(mResult != length){
			mError = SSL_get_error(mSSL, mResult);
			if(mError == SSL_ERROR_WANT_READ|| mError == SSL_ERROR_WANT_WRITE)
				return 0;
		}

		return mResult;
	}

	virtual int write(uint8* data, uint32 length){
		mResult = SSL_write(mSSL, data, length);

		if(mResult != length){
			mError = SSL_get_error(mSSL, mResult);
			if(mError == SSL_ERROR_WANT_READ|| mError == SSL_ERROR_WANT_WRITE)
				return 0;
		}

		return mResult;
	}

	virtual bool canRead(){
		if(SSL_pending(mSSL) > 0)
			return true;

		return Socket::canRead();
	}

	virtual bool canWrite(){
		return Socket::canWrite();
	}

	virtual int getLastError(){
		return mError;
	}

private:
	int mError;
	int mResult;
	SSL* mSSL;
	SSL_CTX* mContext;
};
