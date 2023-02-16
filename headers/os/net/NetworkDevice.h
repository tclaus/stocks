/*
 * Copyright 2010, Haiku, Inc. All Rights Reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _NETWORK_DEVICE_H
#define _NETWORK_DEVICE_H


#include <net/if.h>
#include <string.h>


// authentication modes
enum {
	B_NETWORK_AUTHENTICATION_NONE		= 0,
	B_NETWORK_AUTHENTICATION_WEP		= 1,
	B_NETWORK_AUTHENTICATION_WPA		= 2,
	B_NETWORK_AUTHENTICATION_WPA2		= 3,
	B_NETWORK_AUTHENTICATION_EAP		= 4
};

// cipher algorithms
enum {
	B_NETWORK_CIPHER_NONE				= 0x01,
	B_NETWORK_CIPHER_WEP_40				= 0x02,
	B_NETWORK_CIPHER_WEP_104			= 0x04,
	B_NETWORK_CIPHER_TKIP				= 0x08,
	B_NETWORK_CIPHER_CCMP				= 0x10,
	B_NETWORK_CIPHER_AES_128_CMAC		= 0x20
};

// key modes
enum {
	B_KEY_MODE_IEEE802_1X				= 0x0001,
	B_KEY_MODE_PSK						= 0x0002,
	B_KEY_MODE_NONE						= 0x0004,
	B_KEY_MODE_FT_IEEE802_1X			= 0x0020,
	B_KEY_MODE_FT_PSK					= 0x0040,
	B_KEY_MODE_IEEE802_1X_SHA256		= 0x0080,
	B_KEY_MODE_PSK_SHA256				= 0x0100,
	B_KEY_MODE_WPS						= 0x0200
};

// eap encapsulation method (IEEE 802.1x)
enum {
	B_NETWORK_EAP_ENCAPSULATION_NONE	= 0x0000,
	B_NETWORK_EAP_ENCAPSULATION_PEAP	= 0x0001,
	B_NETWORK_EAP_ENCAPSULATION_TLS		= 0x0002
};


#if defined(__cplusplus) && !defined(_KERNEL_MODE)

#include <NetworkAddress.h>


struct wireless_network {
	char				name[32];
	BNetworkAddress		address;
	uint8				noise_level;
	uint8				signal_strength;
	uint32				flags;
	uint32				authentication_mode;
	uint32				cipher;
	uint32				group_cipher;
	uint32				key_mode;

	bool operator==(const wireless_network& other) {
		return strncmp(name, other.name, 32) == 0
			// ignore address difference
			&& noise_level == other.noise_level
			&& signal_strength == other.signal_strength
			&& flags == other.flags
			&& authentication_mode == other.authentication_mode
			&& cipher == other.cipher
			&& group_cipher == other.group_cipher
			&& key_mode == other.key_mode;
	}
};

// flags
#define B_NETWORK_IS_ENCRYPTED			0x01
#define B_NETWORK_IS_PERSISTENT			0x02


class BNetworkDevice {
public:
								BNetworkDevice();
								BNetworkDevice(const char* name);
								~BNetworkDevice();

			void				Unset();
			void				SetTo(const char* name);

			const char*			Name() const;
			bool				Exists() const;
			uint32				Index() const;

			uint32				Flags() const;
			bool				HasLink() const;

			int32				Media() const;
			status_t			SetMedia(int32 media);

			status_t			GetHardwareAddress(BNetworkAddress& address);

			bool				IsEthernet();
			bool				IsWireless();

			status_t			Control(int option, void* request);

			status_t			Scan(bool wait = true,
									bool forceRescan = true);

			status_t			GetNextNetwork(uint32& cookie,
									wireless_network& network);
			status_t			GetNetworks(wireless_network*& networks,
									uint32& count);
			status_t			GetNetwork(const char* name,
									wireless_network& network);
			status_t			GetNetwork(const BNetworkAddress& address,
									wireless_network& network);

			status_t			JoinNetwork(const char* name,
									const char* password = NULL);
			status_t			JoinNetwork(const wireless_network& network,
									const char* password = NULL);
			status_t			JoinNetwork(const BNetworkAddress& address,
									const char* password = NULL);

			status_t			LeaveNetwork(const char* name);
			status_t			LeaveNetwork(const wireless_network& network);
			status_t			LeaveNetwork(const BNetworkAddress& address);

			status_t			GetNextAssociatedNetwork(uint32& cookie,
									wireless_network& network);
			status_t			GetNextAssociatedNetwork(uint32& cookie,
									BNetworkAddress& address);

private:
			char				fName[IF_NAMESIZE];
};

#endif	// __cplusplus && !_KERNEL_MODE

#endif	// _NETWORK_DEVICE_H
