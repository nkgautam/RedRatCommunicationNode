#include <iostream>
#include <istream>
#include <ostream>
#include <iterator>
#include "BlockChainDataStore.h"

int main() {
	BlockChainDataStore *b = 0;
	int i = 1;
	std::string line;
	while (i && std::getline(std::cin, line)) {
		if (!b) {
			b = new BlockChainDataStore(line.c_str());
			continue;
		}
		switch (i) {
			case 1:
				if (line == "create") {
					i = b->create();
					if (i) std::cout << "Error " << i << " creating '" << b->GetFilespec() << "'" << std::endl;
					else std::cout << "Datastore '" << b->GetFilespec() << "' created" << std::endl;
					i = -1;
					break;
				}
				if (line == "write") {i = 2; continue;}
				if (line == "read") {i = 3; continue;}
				if (line == "verify") {i = 4; continue;}
				if (line == "list") {
					std::vector<off_t> v = b->list();
					// go through the vector
					for (i = 0; i < v.size(); i++)
						std::cout << v[i] << std::endl;
					// if vector is empty print empty
					if (!i) std::cout << "empty" << std::endl;
					i = -1;
					break;
				}
				std::cout << "invalid command: " << line << std::endl;
				i = -1;
				break;
			case 2: { // write
				off_t off = b->write(line);
				std::cout << off << std::endl;
				i = -1;
				break;
				}
			case 3: { // read;
				struct BlockChainData *d = b->read(atol(line.c_str()));
				if (d) {
					*d->currenthash = 0;
					std::cout << (const char *)d->data << std::endl;
					free(d);
				}
				else	std::cout << "Read error" << std::endl;
				i = -1;
				break;
				}
			case 4: { // read and verify;
				struct BlockChainData *d = b->read(atol(line.c_str()));
				if (d) {
					if (b->verify(d)) std::cout << "Verified" << std::endl;
					else	std::cout << "Invalid block found" << std::endl;
					free(d);
				}
				else	std::cout << "Read error" << std::endl;
				i = -1;
				break;
				}
		}

	}
	if (b) delete b;
	else std::cout << "Filespec line not specified" << std::endl;
	if (i > 0) std::cout << "Not enough input lines" << std::endl;
	// std::std::cout << line << std::endl;
	return 0;
}

