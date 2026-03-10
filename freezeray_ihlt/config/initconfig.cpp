#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "fmt/base.h"
#include "..\config\config.hpp"

using namespace std;
using namespace nlohmann;

enum type {
	socks4,
	socks5,
	http,
	shadowsocks,
	ssnew,
	vless,
	vmess,
	xhttp,
	liberty,
	amnezia,
	undefined
};

struct ConfigInfo {
	uint32_t ipv4;
	uint64_t ipv6;
	uint16_t port;
	string domain;
	enum type;
	string uuid;

};

int fv2config::configInfo() {
	ConfigInfo ConfigInfo;

	std::ifstream f("config.json");
	/*json data = json::parse(f);
	std::cout << data << std::endl;
	json search = "{}";
		json found = data.find(search);
		if (found != std::string::npos)
			std::cout << "first 'needle' found at: " << found << '\n';

		/*	enum type config = socks4;


			switch (config) {
			case socks4:
				fmt::print("socks4");
			case socks5:
				fmt::print("socks4");
			case http:
				fmt::print("http");
			case shadowsocks:
				fmt::print("shadowsocks");
			case ssnew:
				fmt::print("ssnew");
			case vless:
				fmt::print("vless");
			case vmess:
				fmt::print("vmess");
			case xhttp:
				fmt::print("xhttp");
			case liberty:
				fmt::print("liberty");
			case amnezia:
				fmt::print("amnezia");
			case undefined:
				fmt::print("undefined");

			/*
					I guess there is some better way to do it, but at least it's fast.
					And maybe secure.

			}
			*/
		return 0;

	}