


#ifdef __cplusplus
extern "C" {
#endif

short ParseOneFrameBits( Word16* serial, AMRStruct* AmrStruct, short nChannel ) ;

//short CombineOneFrameBits( Word16* serial, AMRStruct* AmrStruct, short nChannel ,  enum TXFrameType tx_type, enum Mode mode )  ;
short CombineOneFrameBits(	Word16* serial,	AMRStruct* AmrStruct,	enum TXFrameType tx_type,	enum Mode mode,	short nChannel );
	


#ifdef __cplusplus
}
#endif
