#ifdef __cplusplus
extern "C"{
#endif

#define RNC_COMPRESS_BEST 1
#define RNC_COMPRESS_FAST 2
#define COMPRESSION_UNPACK_BUFFER_EXTEND 20000

unsigned int RNC_Compress(int mode, void *bufferIn, unsigned int length, void **bufferOut);
unsigned int RNC_Uncompress(void *bufferIn, void **bufferOut);
long RNC_UncompressFast(void *input, void *output, unsigned int Len);

#ifdef __cplusplus
}
#endif
