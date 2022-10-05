/*
 * zlib_exports.h - internal header with definitions of all exported functions
 *
 * Copyright (C) 2018 Thorsten Otto
 *
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

#ifndef LIBFUNC
# error "LIBFUNC must be defined before including this file"
#endif
#ifndef LIBFUNC2
#define LIBFUNC2(_fn, name, _nargs) LIBFUNC(_fn, name, _nargs)
#endif

	/*   0 */ LIBFUNC(0, zlib_slb_control, 2)
	/*   1 */ LIBFUNC(1, adler32, 3)
	/*   2 */ LIBFUNC(2, compress, 4)
	/*   3 */ LIBFUNC(3, crc32, 3)
	/*   4 */ LIBFUNC(4, deflate, 2)
	/*   5 */ LIBFUNC(5, deflateCopy, 2)
	/*   6 */ LIBFUNC(6, deflateEnd, 1)
	/*   7 */ LIBFUNC(7, deflateInit2_, 8)
	/*   8 */ LIBFUNC(8, deflateInit_, 4)
	/*   9 */ LIBFUNC(9, deflateParams, 3)
	/*  10 */ LIBFUNC(10, deflateReset, 1)
	/*  11 */ LIBFUNC(11, deflateSetDictionary, 3)
	/*  12 */ LIBFUNC(12, gzclose, 1)
	/*  13 */ LIBFUNC(13, gzdopen, 2)
	/*  14 */ LIBFUNC(14, gzerror, 2)
	/*  15 */ LIBFUNC(15, gzflush, 2)
	/*  16 */ LIBFUNC(16, gzopen, 2)
	/*  17 */ LIBFUNC(17, gzread, 3)
	/*  18 */ LIBFUNC(18, gzwrite, 3)
	/*  19 */ LIBFUNC(19, inflate, 2)
	/*  20 */ LIBFUNC(20, inflateEnd, 1)
	/*  21 */ LIBFUNC(21, inflateInit2_, 4)
	/*  22 */ LIBFUNC(22, inflateInit_, 3)
	/*  23 */ LIBFUNC(23, inflateReset, 1)
	/*  24 */ LIBFUNC(24, inflateSetDictionary, 3)
	/*  25 */ LIBFUNC(25, inflateSync, 1)
	/*  26 */ LIBFUNC(26, uncompress, 4)
	/*  27 */ LIBFUNC(27, zlibVersion, 0)
	/*  28 */ LIBFUNC(28, gzprintf, 20)
	/*  29 */ LIBFUNC(29, gzputc, 2)
	/*  30 */ LIBFUNC(30, gzgetc, 1)
	/*  31 */ LIBFUNC(31, gzseek, 3)
	/*  32 */ LIBFUNC(32, gzrewind, 1)
	/*  33 */ LIBFUNC(33, gztell, 1)
	/*  34 */ LIBFUNC(34, gzeof, 1)
	/*  35 */ LIBFUNC(35, gzsetparams, 3)
	/*  36 */ LIBFUNC(36, zError, 1)
	/*  37 */ LIBFUNC(37, inflateSyncPoint, 1)
	/*  38 */ LIBFUNC(38, get_crc_table, 0)
	/*  39 */ LIBFUNC(39, compress2, 5)
	/*  40 */ LIBFUNC(40, gzputs, 2)
	/*  41 */ LIBFUNC(41, gzgets, 3)
	/*  42 */ LIBFUNC(42, inflateCopy, 2)
	/*  43 */ LIBFUNC(43, inflateBackInit_, 5)
	/*  44 */ LIBFUNC(44, inflateBack, 5)
	/*  45 */ LIBFUNC(45, inflateBackEnd, 1)
	/*  46 */ LIBFUNC(46, compressBound, 1)
	/*  47 */ LIBFUNC(47, deflateBound, 2)
	/*  48 */ LIBFUNC(48, gzclearerr, 1)
	/*  49 */ LIBFUNC(49, gzungetc, 2)
	/*  50 */ LIBFUNC(50, zlibCompileFlags, 0)
	/*  51 */ LIBFUNC(51, deflatePrime, 3)
	/*  52 */ LIBFUNC(52, deflatePending, 3)

	/*  53 */ NOFUNC
	/*  54 */ NOFUNC
	/*  55 */ NOFUNC
	/*  56 */ NOFUNC
	/*  57 */ NOFUNC
	/*  58 */ NOFUNC
	/*  59 */ NOFUNC
	/*  60 */ NOFUNC

	/*  61 */ LIBFUNC(61, unzOpen, 1)
	/*  62 */ LIBFUNC(62, unzClose, 1)
	/*  63 */ LIBFUNC(63, unzGetGlobalInfo, 2)
	/*  64 */ LIBFUNC(64, unzGetCurrentFileInfo, 8)
	/*  65 */ LIBFUNC(65, unzGoToFirstFile, 1)
	/*  66 */ LIBFUNC(66, unzGoToNextFile, 1)
	/*  67 */ LIBFUNC(67, unzOpenCurrentFile, 1)
	/*  68 */ LIBFUNC(68, unzReadCurrentFile, 3)
	/*  69 */ LIBFUNC(69, unzOpenCurrentFile3, 5)
	/*  70 */ LIBFUNC(70, unztell, 1)
	/*  71 */ LIBFUNC(71, unzeof, 1)
	/*  72 */ LIBFUNC(72, unzCloseCurrentFile, 1)
	/*  73 */ LIBFUNC(73, unzGetGlobalComment, 3)
	/*  74 */ LIBFUNC(74, unzStringFileNameCompare, 3)
	/*  75 */ LIBFUNC(75, unzLocateFile, 3)
	/*  76 */ LIBFUNC(76, unzGetLocalExtrafield, 3)
	/*  77 */ LIBFUNC(77, unzOpen2, 2)
	/*  78 */ LIBFUNC(78, unzOpenCurrentFile2, 4)
	/*  79 */ LIBFUNC(79, unzOpenCurrentFilePassword, 2)

	/*  80 */ LIBFUNC(80, zipOpen, 2)
	/*  81 */ LIBFUNC(81, zipOpenNewFileInZip, 10)
	/*  82 */ LIBFUNC(82, zipWriteInFileInZip, 3)
	/*  83 */ LIBFUNC(83, zipCloseFileInZip, 1)
	/*  84 */ LIBFUNC(84, zipClose, 2)
	/*  85 */ NOFUNC
	/*  86 */ LIBFUNC(86, zipOpenNewFileInZip2, 11)
	/*  87 */ LIBFUNC(87, zipCloseFileInZipRaw, 3)
	/*  88 */ LIBFUNC(88, zipOpen2, 4)
	/*  89 */ LIBFUNC(89, zipOpenNewFileInZip3, 16)
	/*  90 */ LIBFUNC(90, zipOpen3, 4)

	/*  91 */ NOFUNC
	/*  92 */ NOFUNC
	/*  93 */ NOFUNC
	/*  94 */ NOFUNC
	/*  95 */ NOFUNC
	/*  96 */ NOFUNC
	/*  97 */ NOFUNC
	/*  98 */ NOFUNC
	/*  99 */ NOFUNC

	/* 100 */ LIBFUNC(100, unzGetFilePos, 2)
	/* 101 */ LIBFUNC(101, unzGoToFilePos, 2)
	/* 102 */ NOFUNC
	/* 103 */ NOFUNC
	/* 104 */ NOFUNC
	/* 105 */ NOFUNC
	/* 106 */ NOFUNC
	/* 107 */ NOFUNC
	/* 108 */ NOFUNC
	/* 109 */ NOFUNC

	/* 110 */ NOFUNC /* fill_win32_filefunc, 1 */

/* zlibwapi v1.2.4 added: */
	/* 111 */ NOFUNC /* fill_win32_filefunc64, 1 */
	/* 112 */ NOFUNC /* fill_win32_filefunc64A, 1 */
	/* 113 */ NOFUNC /* fill_win32_filefunc64W, 1 */
	/* 114 */ NOFUNC
	/* 115 */ NOFUNC
	/* 116 */ NOFUNC
	/* 117 */ NOFUNC
	/* 118 */ NOFUNC
	/* 119 */ NOFUNC

	/* 120 */ LIBFUNC(120, unzOpen64, 1)
	/* 121 */ LIBFUNC(121, unzOpen2_64, 2)
	/* 122 */ LIBFUNC(122, unzGetGlobalInfo64, 2)
	/* 123 */ NOFUNC
	/* 124 */ LIBFUNC(124, unzGetCurrentFileInfo64, 8)
	/* 125 */ LIBFUNC(125, unzGetCurrentFileZStreamPos64, 1)
	/* 126 */ LIBFUNC(126, unztell64, 1)
	/* 127 */ LIBFUNC(127, unzGetFilePos64, 2)
	/* 128 */ LIBFUNC2(128, unzGoToFilePos64, 2)
	/* 129 */ NOFUNC

	/* 130 */ LIBFUNC2(130, zipOpen64, 2)
	/* 131 */ LIBFUNC2(131, zipOpen2_64, 4)
	/* 132 */ LIBFUNC2(132, zipOpenNewFileInZip64, 11)
	/* 133 */ LIBFUNC2(133, zipOpenNewFileInZip2_64, 12)
	/* 134 */ LIBFUNC2(134, zipOpenNewFileInZip3_64, 17)
	/* 135 */ LIBFUNC2(135, zipOpenNewFileInZip4_64, 19)
	/* 136 */ LIBFUNC2(136, zipCloseFileInZipRaw64, 4)
	/* 137 */ NOFUNC
	/* 138 */ NOFUNC
	/* 139 */ NOFUNC

/* zlib1 v1.2.4 added: */
	/* 140 */ LIBFUNC2(140, adler32_combine, 3)
	/* 141 */ LIBFUNC2(141, adler32_combine64, 4)
	/* 142 */ LIBFUNC2(142, crc32_combine, 3)
	/* 143 */ LIBFUNC2(143, crc32_combine64, 4)
	/* 144 */ LIBFUNC2(144, deflateSetHeader, 2)
	/* 145 */ LIBFUNC2(145, deflateTune, 5)
	/* 146 */ LIBFUNC2(146, gzbuffer, 2)
	/* 147 */ LIBFUNC2(147, gzclose_r, 1)
	/* 148 */ LIBFUNC2(148, gzclose_w, 1)
	/* 149 */ LIBFUNC2(149, gzdirect, 1)
	/* 150 */ LIBFUNC2(150, gzoffset, 1)
	/* 151 */ LIBFUNC2(151, gzoffset64, 1) /* FIXME: returns z_off64_t */
	/* 152 */ LIBFUNC2(152, gzopen64, 2)
	/* 153 */ LIBFUNC2(153, gzseek64, 4) /* FIXME: returns z_off64_t */
	/* 154 */ LIBFUNC2(154, gztell64, 1) /* FIXME: returns z_off64_t */
	/* 155 */ NOFUNC
	/* 156 */ LIBFUNC2(156, inflateGetHeader, 2)
	/* 157 */ LIBFUNC2(157, inflateMark, 1)
	/* 158 */ LIBFUNC2(158, inflatePrime, 3)
	/* 159 */ LIBFUNC2(159, inflateReset2, 2)
	/* 160 */ LIBFUNC2(160, inflateUndermine, 2)

/* zlib1 v1.2.6 added: */
	/* 161 */ LIBFUNC2(161, gzgetc_, 1)
	/* 162 */ NOFUNC
	/* 163 */ LIBFUNC2(163, inflateResetKeep, 1)
	/* 164 */ LIBFUNC2(164, deflateResetKeep, 1)

/* zlib1 v1.2.7 added: */
	/* 165 */ NOFUNC  /* gzopen_w, 2 */

/* zlib1 v1.2.8 added: */
	/* 166 */ LIBFUNC2(166, inflateGetDictionary, 3)
	/* 167 */ LIBFUNC2(167, gzvprintf, 3)

/* zlib1 v1.2.9 added: */
	/* 168 */ LIBFUNC2(168, inflateCodesUsed, 1)
	/* 169 */ LIBFUNC2(169, inflateValidate, 2)
	/* 170 */ LIBFUNC2(170, uncompress2, 4)
	/* 171 */ LIBFUNC2(171, gzfread, 4)
	/* 172 */ LIBFUNC2(172, gzfwrite, 4)
	/* 173 */ LIBFUNC2(173, deflateGetDictionary, 3)
	/* 174 */ LIBFUNC2(174, adler32_z, 3)
	/* 175 */ LIBFUNC2(175, crc32_z, 3)

/* zlib1 v1.2.12 added: */
	/* 176 */ LIBFUNC2(176, crc32_combine_gen, 1)
	/* 177 */ LIBFUNC2(177, crc32_combine_gen64, 2)
	/* 178 */ LIBFUNC2(178, crc32_combine_op, 3)

	/* 179 */ NOFUNC
	/* 180 */ NOFUNC
	/* 181 */ NOFUNC
	/* 182 */ NOFUNC
	/* 183 */ NOFUNC
	/* 184 */ NOFUNC
	/* 185 */ NOFUNC
	/* 186 */ NOFUNC
	/* 187 */ NOFUNC
	/* 188 */ NOFUNC
	/* 189 */ NOFUNC
	/* 190 */ NOFUNC
	/* 191 */ NOFUNC
	/* 192 */ NOFUNC
	/* 193 */ NOFUNC
	/* 194 */ NOFUNC
	/* 195 */ NOFUNC
	/* 196 */ NOFUNC
	/* 197 */ NOFUNC
	/* 198 */ NOFUNC
	/* 199 */ NOFUNC

#undef LIBFUNC
#undef LIBFUNC2
#undef NOFUNC
