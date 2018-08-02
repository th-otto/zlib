





 .text






 .dc.l 0x70004afc
 .dc.l _slbname
 .dc.l 0x12b0
 .dc.l 0
 .dc.l zlib_init
 .dc.l zlib_exit
 .dc.l zlib_open
 .dc.l zlib_close

 .dc.l _slh_names



 .dc.l 0
 .dc.l 0,0,0,0,0,0,0

 .dc.l (slh_fend-slh_functions)/4

slh_functions:
           .dc.l _wrap_zlib_set_imports
           .dc.l _wrap_adler32
           .dc.l _wrap_compress
           .dc.l _wrap_crc32
           .dc.l _wrap_deflate
           .dc.l _wrap_deflateCopy
           .dc.l _wrap_deflateEnd
           .dc.l _wrap_deflateInit2_
           .dc.l _wrap_deflateInit_
           .dc.l _wrap_deflateParams
           .dc.l _wrap_deflateReset
           .dc.l _wrap_deflateSetDictionary
           .dc.l _wrap_gzclose
           .dc.l _wrap_gzdopen
           .dc.l _wrap_gzerror
           .dc.l _wrap_gzflush
           .dc.l _wrap_gzopen
           .dc.l _wrap_gzread
           .dc.l _wrap_gzwrite
           .dc.l _wrap_inflate
           .dc.l _wrap_inflateEnd
           .dc.l _wrap_inflateInit2_
           .dc.l _wrap_inflateInit_
           .dc.l _wrap_inflateReset
           .dc.l _wrap_inflateSetDictionary
           .dc.l _wrap_inflateSync
           .dc.l _wrap_uncompress
           .dc.l _wrap_zlibVersion
           .dc.l _wrap_gzprintf
           .dc.l _wrap_gzputc
           .dc.l _wrap_gzgetc
           .dc.l _wrap_gzseek
           .dc.l _wrap_gzrewind
           .dc.l _wrap_gztell
           .dc.l _wrap_gzeof
           .dc.l _wrap_gzsetparams
           .dc.l _wrap_zError
           .dc.l _wrap_inflateSyncPoint
           .dc.l _wrap_get_crc_table
           .dc.l _wrap_compress2
           .dc.l _wrap_gzputs
           .dc.l _wrap_gzgets
           .dc.l _wrap_inflateCopy
           .dc.l _wrap_inflateBackInit_
           .dc.l _wrap_inflateBack
           .dc.l _wrap_inflateBackEnd
           .dc.l _wrap_compressBound
           .dc.l _wrap_deflateBound
           .dc.l _wrap_gzclearerr
           .dc.l _wrap_gzungetc
           .dc.l _wrap_zlibCompileFlags
           .dc.l _wrap_deflatePrime
           .dc.l _wrap_deflatePending
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l _wrap_unzOpen
           .dc.l _wrap_unzClose
           .dc.l _wrap_unzGetGlobalInfo
           .dc.l _wrap_unzGetCurrentFileInfo
           .dc.l _wrap_unzGoToFirstFile
           .dc.l _wrap_unzGoToNextFile
           .dc.l _wrap_unzOpenCurrentFile
           .dc.l _wrap_unzReadCurrentFile
           .dc.l _wrap_unzOpenCurrentFile3
           .dc.l _wrap_unztell
           .dc.l _wrap_unzeof
           .dc.l _wrap_unzCloseCurrentFile
           .dc.l _wrap_unzGetGlobalComment
           .dc.l _wrap_unzStringFileNameCompare
           .dc.l _wrap_unzLocateFile
           .dc.l _wrap_unzGetLocalExtrafield
           .dc.l _wrap_unzOpen2
           .dc.l _wrap_unzOpenCurrentFile2
           .dc.l _wrap_unzOpenCurrentFilePassword
           .dc.l _wrap_zipOpen
           .dc.l _wrap_zipOpenNewFileInZip
           .dc.l _wrap_zipWriteInFileInZip
           .dc.l _wrap_zipCloseFileInZip
           .dc.l _wrap_zipClose
           .dc.l 0
           .dc.l _wrap_zipOpenNewFileInZip2
           .dc.l _wrap_zipCloseFileInZipRaw
           .dc.l _wrap_zipOpen2
           .dc.l _wrap_zipOpenNewFileInZip3
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l _wrap_unzGetFilePos
           .dc.l _wrap_unzGoToFilePos
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l _wrap_unzOpen64
           .dc.l _wrap_unzOpen2_64
           .dc.l _wrap_unzGetGlobalInfo64
           .dc.l 0
           .dc.l _wrap_unzGetCurrentFileInfo64
           .dc.l _wrap_unzGetCurrentFileZStreamPos64
           .dc.l _wrap_unztell64
           .dc.l _wrap_unzGetFilePos64
           .dc.l _wrap_unzGoToFilePos64
           .dc.l 0
           .dc.l _wrap_zipOpen64
           .dc.l _wrap_zipOpen2_64
           .dc.l _wrap_zipOpenNewFileInZip64
           .dc.l _wrap_zipOpenNewFileInZip2_64
           .dc.l _wrap_zipOpenNewFileInZip3_64
           .dc.l _wrap_zipOpenNewFileInZip4_64
           .dc.l _wrap_zipCloseFileInZipRaw64
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l _wrap_adler32_combine
           .dc.l _wrap_adler32_combine64
           .dc.l _wrap_crc32_combine
           .dc.l _wrap_crc32_combine64
           .dc.l _wrap_deflateSetHeader
           .dc.l _wrap_deflateTune
           .dc.l _wrap_gzbuffer
           .dc.l _wrap_gzclose_r
           .dc.l _wrap_gzclose_w
           .dc.l _wrap_gzdirect
           .dc.l _wrap_gzoffset
           .dc.l _wrap_gzoffset64
           .dc.l _wrap_gzopen64
           .dc.l _wrap_gzseek64
           .dc.l _wrap_gztell64
           .dc.l 0
           .dc.l _wrap_inflateGetHeader
           .dc.l _wrap_inflateMark
           .dc.l _wrap_inflatePrime
           .dc.l _wrap_inflateReset2
           .dc.l _wrap_inflateUndermine
           .dc.l _wrap_gzgetc_
           .dc.l 0
           .dc.l _wrap_inflateResetKeep
           .dc.l _wrap_deflateResetKeep
           .dc.l 0

           .dc.l _wrap_inflateGetDictionary
           .dc.l _wrap_gzvprintf


           .dc.l _wrap_inflateCodesUsed
           .dc.l _wrap_inflateValidate
           .dc.l _wrap_uncompress2
           .dc.l _wrap_gzfread
           .dc.l _wrap_gzfwrite
           .dc.l _wrap_deflateGetDictionary
           .dc.l _wrap_adler32_z
           .dc.l _wrap_crc32_z

           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
slh_fend:
           name_zlib_set_imports_str: .ascii "zlib_set_imports"
  .dc.b 0
           name_adler32_str: .ascii "adler32"
  .dc.b 0
           name_compress_str: .ascii "compress"
  .dc.b 0
           name_crc32_str: .ascii "crc32"
  .dc.b 0
           name_deflate_str: .ascii "deflate"
  .dc.b 0
           name_deflateCopy_str: .ascii "deflateCopy"
  .dc.b 0
           name_deflateEnd_str: .ascii "deflateEnd"
  .dc.b 0
           name_deflateInit2__str: .ascii "deflateInit2_"
  .dc.b 0
           name_deflateInit__str: .ascii "deflateInit_"
  .dc.b 0
           name_deflateParams_str: .ascii "deflateParams"
  .dc.b 0
           name_deflateReset_str: .ascii "deflateReset"
  .dc.b 0
           name_deflateSetDictionary_str: .ascii "deflateSetDictionary"
  .dc.b 0
           name_gzclose_str: .ascii "gzclose"
  .dc.b 0
           name_gzdopen_str: .ascii "gzdopen"
  .dc.b 0
           name_gzerror_str: .ascii "gzerror"
  .dc.b 0
           name_gzflush_str: .ascii "gzflush"
  .dc.b 0
           name_gzopen_str: .ascii "gzopen"
  .dc.b 0
           name_gzread_str: .ascii "gzread"
  .dc.b 0
           name_gzwrite_str: .ascii "gzwrite"
  .dc.b 0
           name_inflate_str: .ascii "inflate"
  .dc.b 0
           name_inflateEnd_str: .ascii "inflateEnd"
  .dc.b 0
           name_inflateInit2__str: .ascii "inflateInit2_"
  .dc.b 0
           name_inflateInit__str: .ascii "inflateInit_"
  .dc.b 0
           name_inflateReset_str: .ascii "inflateReset"
  .dc.b 0
           name_inflateSetDictionary_str: .ascii "inflateSetDictionary"
  .dc.b 0
           name_inflateSync_str: .ascii "inflateSync"
  .dc.b 0
           name_uncompress_str: .ascii "uncompress"
  .dc.b 0
           name_zlibVersion_str: .ascii "zlibVersion"
  .dc.b 0
           name_gzprintf_str: .ascii "gzprintf"
  .dc.b 0
           name_gzputc_str: .ascii "gzputc"
  .dc.b 0
           name_gzgetc_str: .ascii "gzgetc"
  .dc.b 0
           name_gzseek_str: .ascii "gzseek"
  .dc.b 0
           name_gzrewind_str: .ascii "gzrewind"
  .dc.b 0
           name_gztell_str: .ascii "gztell"
  .dc.b 0
           name_gzeof_str: .ascii "gzeof"
  .dc.b 0
           name_gzsetparams_str: .ascii "gzsetparams"
  .dc.b 0
           name_zError_str: .ascii "zError"
  .dc.b 0
           name_inflateSyncPoint_str: .ascii "inflateSyncPoint"
  .dc.b 0
           name_get_crc_table_str: .ascii "get_crc_table"
  .dc.b 0
           name_compress2_str: .ascii "compress2"
  .dc.b 0
           name_gzputs_str: .ascii "gzputs"
  .dc.b 0
           name_gzgets_str: .ascii "gzgets"
  .dc.b 0
           name_inflateCopy_str: .ascii "inflateCopy"
  .dc.b 0
           name_inflateBackInit__str: .ascii "inflateBackInit_"
  .dc.b 0
           name_inflateBack_str: .ascii "inflateBack"
  .dc.b 0
           name_inflateBackEnd_str: .ascii "inflateBackEnd"
  .dc.b 0
           name_compressBound_str: .ascii "compressBound"
  .dc.b 0
           name_deflateBound_str: .ascii "deflateBound"
  .dc.b 0
           name_gzclearerr_str: .ascii "gzclearerr"
  .dc.b 0
           name_gzungetc_str: .ascii "gzungetc"
  .dc.b 0
           name_zlibCompileFlags_str: .ascii "zlibCompileFlags"
  .dc.b 0
           name_deflatePrime_str: .ascii "deflatePrime"
  .dc.b 0
           name_deflatePending_str: .ascii "deflatePending"
  .dc.b 0
          
          
          
          
          
          
          
          
           name_unzOpen_str: .ascii "unzOpen"
  .dc.b 0
           name_unzClose_str: .ascii "unzClose"
  .dc.b 0
           name_unzGetGlobalInfo_str: .ascii "unzGetGlobalInfo"
  .dc.b 0
           name_unzGetCurrentFileInfo_str: .ascii "unzGetCurrentFileInfo"
  .dc.b 0
           name_unzGoToFirstFile_str: .ascii "unzGoToFirstFile"
  .dc.b 0
           name_unzGoToNextFile_str: .ascii "unzGoToNextFile"
  .dc.b 0
           name_unzOpenCurrentFile_str: .ascii "unzOpenCurrentFile"
  .dc.b 0
           name_unzReadCurrentFile_str: .ascii "unzReadCurrentFile"
  .dc.b 0
           name_unzOpenCurrentFile3_str: .ascii "unzOpenCurrentFile3"
  .dc.b 0
           name_unztell_str: .ascii "unztell"
  .dc.b 0
           name_unzeof_str: .ascii "unzeof"
  .dc.b 0
           name_unzCloseCurrentFile_str: .ascii "unzCloseCurrentFile"
  .dc.b 0
           name_unzGetGlobalComment_str: .ascii "unzGetGlobalComment"
  .dc.b 0
           name_unzStringFileNameCompare_str: .ascii "unzStringFileNameCompare"
  .dc.b 0
           name_unzLocateFile_str: .ascii "unzLocateFile"
  .dc.b 0
           name_unzGetLocalExtrafield_str: .ascii "unzGetLocalExtrafield"
  .dc.b 0
           name_unzOpen2_str: .ascii "unzOpen2"
  .dc.b 0
           name_unzOpenCurrentFile2_str: .ascii "unzOpenCurrentFile2"
  .dc.b 0
           name_unzOpenCurrentFilePassword_str: .ascii "unzOpenCurrentFilePassword"
  .dc.b 0
           name_zipOpen_str: .ascii "zipOpen"
  .dc.b 0
           name_zipOpenNewFileInZip_str: .ascii "zipOpenNewFileInZip"
  .dc.b 0
           name_zipWriteInFileInZip_str: .ascii "zipWriteInFileInZip"
  .dc.b 0
           name_zipCloseFileInZip_str: .ascii "zipCloseFileInZip"
  .dc.b 0
           name_zipClose_str: .ascii "zipClose"
  .dc.b 0
          
           name_zipOpenNewFileInZip2_str: .ascii "zipOpenNewFileInZip2"
  .dc.b 0
           name_zipCloseFileInZipRaw_str: .ascii "zipCloseFileInZipRaw"
  .dc.b 0
           name_zipOpen2_str: .ascii "zipOpen2"
  .dc.b 0
           name_zipOpenNewFileInZip3_str: .ascii "zipOpenNewFileInZip3"
  .dc.b 0
          
          
          
          
          
          
          
          
          
          
           name_unzGetFilePos_str: .ascii "unzGetFilePos"
  .dc.b 0
           name_unzGoToFilePos_str: .ascii "unzGoToFilePos"
  .dc.b 0
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
           name_unzOpen64_str: .ascii "unzOpen64"
  .dc.b 0
           name_unzOpen2_64_str: .ascii "unzOpen2_64"
  .dc.b 0
           name_unzGetGlobalInfo64_str: .ascii "unzGetGlobalInfo64"
  .dc.b 0
          
           name_unzGetCurrentFileInfo64_str: .ascii "unzGetCurrentFileInfo64"
  .dc.b 0
           name_unzGetCurrentFileZStreamPos64_str: .ascii "unzGetCurrentFileZStreamPos64"
  .dc.b 0
           name_unztell64_str: .ascii "unztell64"
  .dc.b 0
           name_unzGetFilePos64_str: .ascii "unzGetFilePos64"
  .dc.b 0
           name_unzGoToFilePos64_str: .ascii "unzGoToFilePos64"
  .dc.b 0
          
           name_zipOpen64_str: .ascii "zipOpen64"
  .dc.b 0
           name_zipOpen2_64_str: .ascii "zipOpen2_64"
  .dc.b 0
           name_zipOpenNewFileInZip64_str: .ascii "zipOpenNewFileInZip64"
  .dc.b 0
           name_zipOpenNewFileInZip2_64_str: .ascii "zipOpenNewFileInZip2_64"
  .dc.b 0
           name_zipOpenNewFileInZip3_64_str: .ascii "zipOpenNewFileInZip3_64"
  .dc.b 0
           name_zipOpenNewFileInZip4_64_str: .ascii "zipOpenNewFileInZip4_64"
  .dc.b 0
           name_zipCloseFileInZipRaw64_str: .ascii "zipCloseFileInZipRaw64"
  .dc.b 0
          
          
          
           name_adler32_combine_str: .ascii "adler32_combine"
  .dc.b 0
           name_adler32_combine64_str: .ascii "adler32_combine64"
  .dc.b 0
           name_crc32_combine_str: .ascii "crc32_combine"
  .dc.b 0
           name_crc32_combine64_str: .ascii "crc32_combine64"
  .dc.b 0
           name_deflateSetHeader_str: .ascii "deflateSetHeader"
  .dc.b 0
           name_deflateTune_str: .ascii "deflateTune"
  .dc.b 0
           name_gzbuffer_str: .ascii "gzbuffer"
  .dc.b 0
           name_gzclose_r_str: .ascii "gzclose_r"
  .dc.b 0
           name_gzclose_w_str: .ascii "gzclose_w"
  .dc.b 0
           name_gzdirect_str: .ascii "gzdirect"
  .dc.b 0
           name_gzoffset_str: .ascii "gzoffset"
  .dc.b 0
           name_gzoffset64_str: .ascii "gzoffset64"
  .dc.b 0
           name_gzopen64_str: .ascii "gzopen64"
  .dc.b 0
           name_gzseek64_str: .ascii "gzseek64"
  .dc.b 0
           name_gztell64_str: .ascii "gztell64"
  .dc.b 0
          
           name_inflateGetHeader_str: .ascii "inflateGetHeader"
  .dc.b 0
           name_inflateMark_str: .ascii "inflateMark"
  .dc.b 0
           name_inflatePrime_str: .ascii "inflatePrime"
  .dc.b 0
           name_inflateReset2_str: .ascii "inflateReset2"
  .dc.b 0
           name_inflateUndermine_str: .ascii "inflateUndermine"
  .dc.b 0
           name_gzgetc__str: .ascii "gzgetc_"
  .dc.b 0
          
           name_inflateResetKeep_str: .ascii "inflateResetKeep"
  .dc.b 0
           name_deflateResetKeep_str: .ascii "deflateResetKeep"
  .dc.b 0
          
           name_inflateGetDictionary_str: .ascii "inflateGetDictionary"
  .dc.b 0
           name_gzvprintf_str: .ascii "gzvprintf"
  .dc.b 0
           name_inflateCodesUsed_str: .ascii "inflateCodesUsed"
  .dc.b 0
           name_inflateValidate_str: .ascii "inflateValidate"
  .dc.b 0
           name_uncompress2_str: .ascii "uncompress2"
  .dc.b 0
           name_gzfread_str: .ascii "gzfread"
  .dc.b 0
           name_gzfwrite_str: .ascii "gzfwrite"
  .dc.b 0
           name_deflateGetDictionary_str: .ascii "deflateGetDictionary"
  .dc.b 0
           name_adler32_z_str: .ascii "adler32_z"
  .dc.b 0
           name_crc32_z_str: .ascii "crc32_z"
  .dc.b 0
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
 .even
_slh_names:
           .dc.l name_zlib_set_imports_str
           .dc.l name_adler32_str
           .dc.l name_compress_str
           .dc.l name_crc32_str
           .dc.l name_deflate_str
           .dc.l name_deflateCopy_str
           .dc.l name_deflateEnd_str
           .dc.l name_deflateInit2__str
           .dc.l name_deflateInit__str
           .dc.l name_deflateParams_str
           .dc.l name_deflateReset_str
           .dc.l name_deflateSetDictionary_str
           .dc.l name_gzclose_str
           .dc.l name_gzdopen_str
           .dc.l name_gzerror_str
           .dc.l name_gzflush_str
           .dc.l name_gzopen_str
           .dc.l name_gzread_str
           .dc.l name_gzwrite_str
           .dc.l name_inflate_str
           .dc.l name_inflateEnd_str
           .dc.l name_inflateInit2__str
           .dc.l name_inflateInit__str
           .dc.l name_inflateReset_str
           .dc.l name_inflateSetDictionary_str
           .dc.l name_inflateSync_str
           .dc.l name_uncompress_str
           .dc.l name_zlibVersion_str
           .dc.l name_gzprintf_str
           .dc.l name_gzputc_str
           .dc.l name_gzgetc_str
           .dc.l name_gzseek_str
           .dc.l name_gzrewind_str
           .dc.l name_gztell_str
           .dc.l name_gzeof_str
           .dc.l name_gzsetparams_str
           .dc.l name_zError_str
           .dc.l name_inflateSyncPoint_str
           .dc.l name_get_crc_table_str
           .dc.l name_compress2_str
           .dc.l name_gzputs_str
           .dc.l name_gzgets_str
           .dc.l name_inflateCopy_str
           .dc.l name_inflateBackInit__str
           .dc.l name_inflateBack_str
           .dc.l name_inflateBackEnd_str
           .dc.l name_compressBound_str
           .dc.l name_deflateBound_str
           .dc.l name_gzclearerr_str
           .dc.l name_gzungetc_str
           .dc.l name_zlibCompileFlags_str
           .dc.l name_deflatePrime_str
           .dc.l name_deflatePending_str
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l name_unzOpen_str
           .dc.l name_unzClose_str
           .dc.l name_unzGetGlobalInfo_str
           .dc.l name_unzGetCurrentFileInfo_str
           .dc.l name_unzGoToFirstFile_str
           .dc.l name_unzGoToNextFile_str
           .dc.l name_unzOpenCurrentFile_str
           .dc.l name_unzReadCurrentFile_str
           .dc.l name_unzOpenCurrentFile3_str
           .dc.l name_unztell_str
           .dc.l name_unzeof_str
           .dc.l name_unzCloseCurrentFile_str
           .dc.l name_unzGetGlobalComment_str
           .dc.l name_unzStringFileNameCompare_str
           .dc.l name_unzLocateFile_str
           .dc.l name_unzGetLocalExtrafield_str
           .dc.l name_unzOpen2_str
           .dc.l name_unzOpenCurrentFile2_str
           .dc.l name_unzOpenCurrentFilePassword_str
           .dc.l name_zipOpen_str
           .dc.l name_zipOpenNewFileInZip_str
           .dc.l name_zipWriteInFileInZip_str
           .dc.l name_zipCloseFileInZip_str
           .dc.l name_zipClose_str
           .dc.l 0
           .dc.l name_zipOpenNewFileInZip2_str
           .dc.l name_zipCloseFileInZipRaw_str
           .dc.l name_zipOpen2_str
           .dc.l name_zipOpenNewFileInZip3_str
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l name_unzGetFilePos_str
           .dc.l name_unzGoToFilePos_str
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l name_unzOpen64_str
           .dc.l name_unzOpen2_64_str
           .dc.l name_unzGetGlobalInfo64_str
           .dc.l 0
           .dc.l name_unzGetCurrentFileInfo64_str
           .dc.l name_unzGetCurrentFileZStreamPos64_str
           .dc.l name_unztell64_str
           .dc.l name_unzGetFilePos64_str
           .dc.l name_unzGoToFilePos64_str
           .dc.l 0
           .dc.l name_zipOpen64_str
           .dc.l name_zipOpen2_64_str
           .dc.l name_zipOpenNewFileInZip64_str
           .dc.l name_zipOpenNewFileInZip2_64_str
           .dc.l name_zipOpenNewFileInZip3_64_str
           .dc.l name_zipOpenNewFileInZip4_64_str
           .dc.l name_zipCloseFileInZipRaw64_str
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l name_adler32_combine_str
           .dc.l name_adler32_combine64_str
           .dc.l name_crc32_combine_str
           .dc.l name_crc32_combine64_str
           .dc.l name_deflateSetHeader_str
           .dc.l name_deflateTune_str
           .dc.l name_gzbuffer_str
           .dc.l name_gzclose_r_str
           .dc.l name_gzclose_w_str
           .dc.l name_gzdirect_str
           .dc.l name_gzoffset_str
           .dc.l name_gzoffset64_str
           .dc.l name_gzopen64_str
           .dc.l name_gzseek64_str
           .dc.l name_gztell64_str
           .dc.l 0
           .dc.l name_inflateGetHeader_str
           .dc.l name_inflateMark_str
           .dc.l name_inflatePrime_str
           .dc.l name_inflateReset2_str
           .dc.l name_inflateUndermine_str
           .dc.l name_gzgetc__str
           .dc.l 0
           .dc.l name_inflateResetKeep_str
           .dc.l name_deflateResetKeep_str
           .dc.l 0
           .dc.l name_inflateGetDictionary_str
           .dc.l name_gzvprintf_str
           .dc.l name_inflateCodesUsed_str
           .dc.l name_inflateValidate_str
           .dc.l name_uncompress2_str
           .dc.l name_gzfread_str
           .dc.l name_gzfwrite_str
           .dc.l name_deflateGetDictionary_str
           .dc.l name_adler32_z_str
           .dc.l name_crc32_z_str
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           .dc.l 0
           _wrap_zlib_set_imports : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zlib_set_imports
           _wrap_adler32 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp adler32
           _wrap_compress : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp compress
           _wrap_crc32 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp crc32
           _wrap_deflate : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflate
           _wrap_deflateCopy : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateCopy
           _wrap_deflateEnd : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateEnd
           _wrap_deflateInit2_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateInit2_
           _wrap_deflateInit_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateInit_
           _wrap_deflateParams : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateParams
           _wrap_deflateReset : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateReset
           _wrap_deflateSetDictionary : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateSetDictionary
           _wrap_gzclose : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzclose
           _wrap_gzdopen : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzdopen
           _wrap_gzerror : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzerror
           _wrap_gzflush : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzflush
           _wrap_gzopen : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzopen
           _wrap_gzread : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzread
           _wrap_gzwrite : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzwrite
           _wrap_inflate : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflate
           _wrap_inflateEnd : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateEnd
           _wrap_inflateInit2_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateInit2_
           _wrap_inflateInit_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateInit_
           _wrap_inflateReset : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateReset
           _wrap_inflateSetDictionary : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateSetDictionary
           _wrap_inflateSync : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateSync
           _wrap_uncompress : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp uncompress
           _wrap_zlibVersion : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zlibVersion
           _wrap_gzprintf : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzprintf
           _wrap_gzputc : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzputc
           _wrap_gzgetc : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzgetc
           _wrap_gzseek : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzseek
           _wrap_gzrewind : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzrewind
           _wrap_gztell : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gztell
           _wrap_gzeof : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzeof
           _wrap_gzsetparams : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzsetparams
           _wrap_zError : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zError
           _wrap_inflateSyncPoint : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateSyncPoint
           _wrap_get_crc_table : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp get_crc_table
           _wrap_compress2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp compress2
           _wrap_gzputs : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzputs
           _wrap_gzgets : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzgets
           _wrap_inflateCopy : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateCopy
           _wrap_inflateBackInit_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateBackInit_
           _wrap_inflateBack : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateBack
           _wrap_inflateBackEnd : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateBackEnd
           _wrap_compressBound : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp compressBound
           _wrap_deflateBound : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateBound
           _wrap_gzclearerr : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzclearerr
           _wrap_gzungetc : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzungetc
           _wrap_zlibCompileFlags : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zlibCompileFlags
           _wrap_deflatePrime : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflatePrime
           _wrap_deflatePending : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflatePending
          
          
          
          
          
          
          
          
           _wrap_unzOpen : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpen
           _wrap_unzClose : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzClose
           _wrap_unzGetGlobalInfo : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetGlobalInfo
           _wrap_unzGetCurrentFileInfo : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetCurrentFileInfo
           _wrap_unzGoToFirstFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGoToFirstFile
           _wrap_unzGoToNextFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGoToNextFile
           _wrap_unzOpenCurrentFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpenCurrentFile
           _wrap_unzReadCurrentFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzReadCurrentFile
           _wrap_unzOpenCurrentFile3 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpenCurrentFile3
           _wrap_unztell : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unztell
           _wrap_unzeof : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzeof
           _wrap_unzCloseCurrentFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzCloseCurrentFile
           _wrap_unzGetGlobalComment : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetGlobalComment
           _wrap_unzStringFileNameCompare : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzStringFileNameCompare
           _wrap_unzLocateFile : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzLocateFile
           _wrap_unzGetLocalExtrafield : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetLocalExtrafield
           _wrap_unzOpen2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpen2
           _wrap_unzOpenCurrentFile2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpenCurrentFile2
           _wrap_unzOpenCurrentFilePassword : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpenCurrentFilePassword
           _wrap_zipOpen : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpen
           _wrap_zipOpenNewFileInZip : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip
           _wrap_zipWriteInFileInZip : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipWriteInFileInZip
           _wrap_zipCloseFileInZip : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipCloseFileInZip
           _wrap_zipClose : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipClose
          
           _wrap_zipOpenNewFileInZip2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip2
           _wrap_zipCloseFileInZipRaw : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipCloseFileInZipRaw
           _wrap_zipOpen2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpen2
           _wrap_zipOpenNewFileInZip3 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip3
          
          
          
          
          
          
          
          
          
          
           _wrap_unzGetFilePos : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetFilePos
           _wrap_unzGoToFilePos : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGoToFilePos
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
           _wrap_unzOpen64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpen64
           _wrap_unzOpen2_64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzOpen2_64
           _wrap_unzGetGlobalInfo64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetGlobalInfo64
          
           _wrap_unzGetCurrentFileInfo64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetCurrentFileInfo64
           _wrap_unzGetCurrentFileZStreamPos64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetCurrentFileZStreamPos64
           _wrap_unztell64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unztell64
           _wrap_unzGetFilePos64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGetFilePos64
           _wrap_unzGoToFilePos64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp unzGoToFilePos64
          
           _wrap_zipOpen64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpen64
           _wrap_zipOpen2_64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpen2_64
           _wrap_zipOpenNewFileInZip64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip64
           _wrap_zipOpenNewFileInZip2_64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip2_64
           _wrap_zipOpenNewFileInZip3_64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip3_64
           _wrap_zipOpenNewFileInZip4_64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipOpenNewFileInZip4_64
           _wrap_zipCloseFileInZipRaw64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp zipCloseFileInZipRaw64
          
          
          
           _wrap_adler32_combine : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp adler32_combine
           _wrap_adler32_combine64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp adler32_combine64
           _wrap_crc32_combine : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp crc32_combine
           _wrap_crc32_combine64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp crc32_combine64
           _wrap_deflateSetHeader : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateSetHeader
           _wrap_deflateTune : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateTune
           _wrap_gzbuffer : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzbuffer
           _wrap_gzclose_r : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzclose_r
           _wrap_gzclose_w : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzclose_w
           _wrap_gzdirect : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzdirect
           _wrap_gzoffset : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzoffset
           _wrap_gzoffset64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzoffset64
           _wrap_gzopen64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzopen64
           _wrap_gzseek64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzseek64
           _wrap_gztell64 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gztell64
          
           _wrap_inflateGetHeader : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateGetHeader
           _wrap_inflateMark : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateMark
           _wrap_inflatePrime : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflatePrime
           _wrap_inflateReset2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateReset2
           _wrap_inflateUndermine : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateUndermine
           _wrap_gzgetc_ : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzgetc_
          
           _wrap_inflateResetKeep : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateResetKeep
           _wrap_deflateResetKeep : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateResetKeep
          
           _wrap_inflateGetDictionary : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateGetDictionary
           _wrap_gzvprintf : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzvprintf
           _wrap_inflateCodesUsed : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateCodesUsed
           _wrap_inflateValidate : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp inflateValidate
           _wrap_uncompress2 : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp uncompress2
           _wrap_gzfread : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzfread
           _wrap_gzfwrite : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp gzfwrite
           _wrap_deflateGetDictionary : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp deflateGetDictionary
           _wrap_adler32_z : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp adler32_z
           _wrap_crc32_z : move.l (a7)+,d0
  move.l (a7)+,a0
  addq.l #4,a7
  move.l d0,(a7)
  jmp crc32_z
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
_slbname: .ascii "zlib.slb"
 .dc.b 0
 .even
