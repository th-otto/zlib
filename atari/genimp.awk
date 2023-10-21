#!/usr/bin/awk -f

BEGIN {
	inif = 0;
	inelse = 0;
	funcno = 0;
	ifstartfunc = 0;
	ifdef = "";
}

/^#if/ || /^#ifndef/ {
	if (inif != 0) {
		print "cannot handle nested #if" > "/dev/stderr";
		exit(1);
	}
	inif++;
	ifdef = $0;
	next;
}

/^#else/ {
	if (inif == 0) {
		print "#else without #if" > "/dev/stderr";
		exit(1);
	}
	inelse = 1;
	next;
}

/^#endif/ {
	if (inif == 0) {
		print "#endif without #if" > "/dev/stderr";
		exit(1);
	}
	inif--;
	if (inelse != 0 && ifstartfunc != funcno) {
		print "nonmatching NOFUNCs" > "/dev/stderr";
		exit(1);
	}
	inelse = 0;
	ifdef = "";
	next;
}

/^#define/ {
		next;
	   }

/^#undef/ {
		next;
	  }

/^#error/ {
		next;
	  }

/^#/	{
		printf("%d: unrecognized preprocessor: %s\n", NR, $0) > "/dev/stderr";
		exit(1);
	}

{
	if (match($0, /^.*LIBFUNC.*\(([0-9]+).*$/, a)) {
		file = "zimp_" a[1] ".c";
		print "#include \"zlib_imp.h\"" > file;
		if (inif == 1)
			print ifdef > file;
		printf("/* %4d */ %s\n", funcno, a[0]) > file;
		if (inif == 1)
			print "#endif" > file;
		close(file);
		++funcno;
	} else if (match($0, /^(.*)(NOFUNC)(.*)$/, a) && inif == 0 && $1 != "#undef") {
		file = "zimp_" funcno ".c";
		print "#include \"zlib_imp.h\"" > file;
		close(file);
		++funcno;
	} else if (match($0, /^(.*)(NOFUNC)(.*)$/, a) && inelse != 0) {
		++ifstartfunc;
	}
}
