/*
 * Copyright 2011-2016, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _ABSTRACT_SOCKET_H
#define _ABSTRACT_SOCKET_H


#include <DataIO.h>
#include <NetworkAddress.h>

#include <sys/socket.h>


class BAbstractSocket : public BDataIO {
public:
								BAbstractSocket();
								BAbstractSocket(const BAbstractSocket& other);
	virtual						~BAbstractSocket();

			status_t			InitCheck() const;

	virtual status_t			Bind(const BNetworkAddress& local, bool reuseAddr) = 0;
	virtual bool				IsBound() const;
	virtual	bool				IsListening() const;

	virtual	status_t			Listen(int backlog = 10);
	virtual	status_t			Accept(BAbstractSocket*& _socket) = 0;

	virtual	status_t			Connect(const BNetworkAddress& peer,
									bigtime_t timeout = B_INFINITE_TIMEOUT) = 0;
	virtual	bool				IsConnected() const;
	virtual	void				Disconnect();

	virtual	status_t			SetTimeout(bigtime_t timeout);
	virtual	bigtime_t			Timeout() const;

	virtual	const BNetworkAddress& Local() const;
	virtual	const BNetworkAddress& Peer() const;

	virtual	size_t				MaxTransmissionSize() const;

	virtual	status_t			WaitForReadable(bigtime_t timeout
										= B_INFINITE_TIMEOUT) const;
	virtual	status_t			WaitForWritable(bigtime_t timeout
										= B_INFINITE_TIMEOUT) const;

			int					Socket() const;

protected:
			status_t			Bind(const BNetworkAddress& local,
									bool reuseAddr, int type);
			status_t			Connect(const BNetworkAddress& peer, int type,
									bigtime_t timeout = B_INFINITE_TIMEOUT);
			status_t			AcceptNext(int& _acceptedSocket,
									BNetworkAddress& _peer);

private:
			status_t			_OpenIfNeeded(int family, int type);
			status_t			_UpdateLocalAddress();
			status_t			_WaitFor(int flags, bigtime_t timeout) const;

protected:
			status_t			fInitStatus;
			int					fSocket;
			BNetworkAddress		fLocal;
			BNetworkAddress		fPeer;
			bool				fIsBound;
			bool				fIsConnected;
			bool				fIsListening;
};


#endif	// _ABSTRACT_SOCKET_H
