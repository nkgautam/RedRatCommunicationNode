#ifndef BLOCKCHAINDATASTORE_H
#define BLOCKCHAINDATASTORE_H

#include <vector>
#include <string>
#include "sha256.h"

struct BlockChainData {
	unsigned char *currenthash;			// hash of this block (will point to data[length])
	unsigned char priorhash[SHA256::DIGEST_SIZE];	// start point of hash calculation, read. Returned filepointer from write
	int length;					// length of data, start point of write.
	unsigned char data[1];				// [length + SHA256:DIGEST_SIZE]
							// end point of hash calculation: data[length]
							// end point of write: data[length + SHA:DIGEST_SIZE]
};


class BlockChainDataStore
{
    public:
        BlockChainDataStore(const char *filespec);
        virtual ~BlockChainDataStore();
	int create();	// initializes a new store. 0 on success, < 0 on error
	off_t write(const void *data, int length); // returns offset of block, < 0 on error
	off_t write(std::string str); // returns offset of block, < 0 on error
	struct BlockChainData *read(off_t offset); // returns filled in struct or NULL on error
	bool verify(const struct BlockChainData *input); // returns true if structure's hash is correct
	std::vector<off_t> list(); // returns offsets of the blocks

        std::string GetFilespec() { return m_Filespec; }
        void SetFilespec(std::string val) { m_Filespec = val; }

    protected:

    private:
	struct BlockChainData *allocate(int length);
	void calculate_hash(struct BlockChainData *block);
        std::string m_Filespec;
};

#endif // BLOCKCHAINDATASTORE_H
