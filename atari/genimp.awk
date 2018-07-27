#!/usr/bin/awk -f

BEGIN {
	inif = 0;
	ifdef = "";
}

/^#if/ {
	inif = 1;
	ifdef = $0;
}

/^#else/ {
	inif = 2;
}

/^#endif/ {
	inif = 0;
	ifdef = "";
}

{
	if (match($0, /^.*LIBFUNC.*\(([0-9]+).*$/, a)) {
		file = "zlib_imp_" a[1] ".c";
		print "#include \"zlib_imp.h\"" > file;
		if (inif == 1)
			print ifdef > file;
		print a[0] > file;
		if (inif == 1)
			print "#endif" > file;
		close(file);
	}
}
