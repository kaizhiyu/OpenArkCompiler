/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reverved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1. 
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 * 	http://license.coscl.org.cn/MulanPSL 
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v1 for more details.  
 */

/*
 * This header file and associated patches provide a decoder for PKWare's
 * undocumented deflate64 compression method (method 9).  Use with infback9.c,
 * inftree9.h, inftree9.c, and inffix9.h.  These patches are not supported.
 * This should be compiled with zlib, since it uses zutil.h and zutil.o.
 * This code has not yet been tested on 16-bit architectures.  See the
 * comments in zlib.h for inflateBack() usage.  These functions are used
 * identically, except that there is no windowBits parameter, and a 64K
 * window must be provided.  Also if int's are 16 bits, then a zero for
 * the third parameter of the "out" function actually means 65536UL.
 * zlib.h must be included before this header file.
 */

#ifdef __cplusplus
extern "C" {
#endif

ZEXTERN int ZEXPORT inflateBack9 OF((z_stream FAR *strm,
                                    in_func in, void FAR *in_desc,
                                    out_func out, void FAR *out_desc));
ZEXTERN int ZEXPORT inflateBack9End OF((z_stream FAR *strm));
ZEXTERN int ZEXPORT inflateBack9Init_ OF((z_stream FAR *strm,
                                         unsigned char FAR *window,
                                         const char *version,
                                         int stream_size));
#define inflateBack9Init(strm, window) \
        inflateBack9Init_((strm), (window), \
        ZLIB_VERSION, sizeof(z_stream))

#ifdef __cplusplus
}
#endif
