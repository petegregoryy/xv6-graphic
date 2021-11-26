#!/usr/bin/perl -w

# Generate syscall.h, syscalltable.h or usys.S. These are the header and assembly
# files for system calls.
#
# Generating these files from one script avoids them getting out of sync. 
# 
# Specify an argument of -h to generate syscall.h
# Specify an argument of -c to generate syscalltable.h
# Specify an argument of -a to generate usys.S
#
# Note that you also need to update user.h with the declarations for these functions that
# user programs will use.  This ensures that the C compiler generates the correct code to 
# push the parameters on to the stack. 

my @syscalls = (
				"fork", 
				"exit", 
				"wait", 
				"pipe", 
				"read", 
				"kill", 
				"exec", 
				"fstat",
                "chdir",
				"dup", 
				"getpid",
				"sbrk", 
				"sleep", 
				"uptime", 
				"open", 
				"write", 
                "mknod",
                "unlink",
                "link",
                "mkdir",
				"close",
                "getch",
				"shutdown",
				"setvideomode",
				"setpixelSys",
				"movetoSys",
				"linetoSys",
				"ping",
				"flushscreen",
				"selectpenSys",
				"setpencolourSys",
				"fillrectSys",
				"beginpaint",
				"endpaintSys",
				"executedraw"
			   );

my $i;			   
if ($#ARGV == -1)
{
	print 'Error: No argument supplied to gensyscalls.pl';
	exit(1);
}
if (($ARGV[0] ne '-h') && ($ARGV[0] ne '-a') && ($ARGV[0] ne '-c'))
{
	print 'Error: Invalid argument to gensyscalls.pl';
	exit(1);
}
if ($ARGV[0] eq '-h'|| $ARGV[0] eq '-c')
{
	print "// Generated by gensyscalls.pl.  Do not edit.\n";
	print "// To change syscall numbers or add new syscalls, edit gensyscalls.pl\n";
	print "\n";
}
else
{
	print "# Generated by gensyscalls.pl.  Do not edit.\n";
	print "# To change syscall numbers or add new syscalls, edit gensyscalls.pl\n";
	print "\n";
}
for ($i = 0; $i < scalar(@syscalls); $i++)
{
	my $index = $i + 1;
	if ($ARGV[0] eq '-h')
	{
		print "#define SYS_$syscalls[$i]\t\t$index\n";
	}
	elsif ($ARGV[0] eq '-c')
	{
		print "extern int sys_$syscalls[$i](void);\n";
	}
}
if ($ARGV[0] eq '-a')
{
	print "#include \"syscall.h\"\n";
	print "#include \"traps.h\"\n";
	print "\n";
	print "#define SYSCALL(name) \\\n";
	print ".globl name; \\\n"; 
	print "name: \\\n"; 
    print "\tmovl\t\$SYS_ ## name, \%eax; \\\n"; 
    print "\tint\t\$T_SYSCALL; \\\n"; 
    print "\tret\n";
	print "\n";
	for ($i = 0; $i < scalar(@syscalls); $i++)
	{
		print "SYSCALL($syscalls[$i])\n";
	}
}
elsif ($ARGV[0] eq '-c')
{
	print "\n";
	print "static int(*syscalls[])(void) = {\n";
	for ($i = 0; $i < scalar(@syscalls); $i++)
	{
		print "[SYS_$syscalls[$i]]\tsys_$syscalls[$i],\n";
	}
	print "};\n"
}
