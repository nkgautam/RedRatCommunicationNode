#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "BlockChainDataStore.h"

BlockChainDataStore::BlockChainDataStore(const char *filespec)
{
    //ctor
    m_Filespec = filespec;
}

BlockChainDataStore::~BlockChainDataStore()
{
    //dtor
}


int BlockChainDataStore::create() {
	int fh = open(m_Filespec.c_str(), O_CREAT | O_EXCL | O_WRONLY, __S_IREAD | __S_IWRITE);
	if (fh == -1) return -1;
	BlockChainData *b = allocate(m_Filespec.length());
	// seed the prior hash
	time((time_t *)b->priorhash);
	strcpy((char *)&b->priorhash[sizeof(time_t)], "BlockChainDataStore");
	strcpy((char *)b->data, m_Filespec.c_str());
	calculate_hash(b);
	size_t ct = ::write(fh, (const void *)b->currenthash, SHA256::DIGEST_SIZE);
	close(fh);
	free(b);
	return (ct == SHA256::DIGEST_SIZE) ? 0 : -2;
}

off_t BlockChainDataStore::write(const void *data, int length) {
	int fh = open(m_Filespec.c_str(), O_RDWR);
	if (fh == -1) return -1;
	struct BlockChainData *b = allocate(length);
	// get the position where we will write the data
	off_t ret = lseek(fh, 0, SEEK_END);
	if (ret < SHA256::DIGEST_SIZE) {
		close(fh);
		return -2;
	}
	// seed the prior hash
	lseek(fh, ret - SHA256::DIGEST_SIZE, SEEK_SET);
	::read(fh, b->priorhash, SHA256::DIGEST_SIZE);
	memcpy(b->data, data, length);
	calculate_hash(b);
	length += SHA256::DIGEST_SIZE + sizeof(int);
	size_t ct = ::write(fh, (const void *)&b->length, length);
	close(fh);
	free(b);
	if (ct == (size_t)length) return ret;
	return -2;
}

off_t BlockChainDataStore::write(std::string str) {
	return write(str.c_str(), str.length());
}

struct BlockChainData *BlockChainDataStore::read(off_t offset) {
	int fh = open(m_Filespec.c_str(), O_RDONLY);
	if (fh == -1) return NULL;
	struct BlockChainData tmp, *b;
	b = &tmp;
	// seed the prior hash and length
	lseek(fh, offset - SHA256::DIGEST_SIZE, SEEK_SET);
	::read(fh, b->priorhash, SHA256::DIGEST_SIZE + sizeof(int));
	b = allocate(b->length);
	memcpy(b->priorhash, tmp.priorhash, SHA256::DIGEST_SIZE);
	::read(fh, b->data, b->length + SHA256::DIGEST_SIZE);
	close(fh);
	return b;
}

bool BlockChainDataStore::verify(const struct BlockChainData *input) {
	unsigned char digest[SHA256::DIGEST_SIZE];
	sha256(input->priorhash, SHA256::DIGEST_SIZE + sizeof(int) + input->length, digest);
	return (memcmp(input->currenthash, digest, sizeof(digest)) == 0);
}

std::vector<off_t> BlockChainDataStore::list() {
	std::vector<off_t> ret;
	int fh = open(m_Filespec.c_str(), O_RDONLY);
	if (fh == -1) return ret;
	int length;
	off_t off = SHA256::DIGEST_SIZE;
	off_t len = lseek(fh, 0, SEEK_END);
	off_t inc = SHA256::DIGEST_SIZE + sizeof(int);
	while (off <= len) {
		lseek(fh, off, SEEK_SET);
		if (::read(fh, &length, sizeof(int)) != sizeof(int)) break;
		ret.push_back(off);
		off += length + inc;
	}
	return ret;
}

struct BlockChainData *BlockChainDataStore::allocate(int length) {
	struct BlockChainData *ret = (struct BlockChainData *)malloc(sizeof(struct BlockChainData) + length);
	ret->length = length;
	ret->currenthash = &ret->data[length];
	return ret;
}

void BlockChainDataStore::calculate_hash(struct BlockChainData *block) {
	sha256(block->priorhash, SHA256::DIGEST_SIZE + sizeof(int) + block->length, block->currenthash);
}

