
#inpname = "_funclist_winhttp.txt"
#inpname = "_funclist_wininet.txt"
#inpname = "_funclist_ws2_32.txt"
inpname = "_funclist_console.txt"

with open(inpname) as f:
	content = f.readlines()
# you may also want to remove whitespace characters like `\n` at the end of each line
content = [x.strip() for x in content] 
print(content)

for func in content:
	onefunc = """BOOL Hook_"""+func+"""() {
    std::cout << "\\n Hook_"""+func+""" \\n\\n";
    char buf[500] = \""""+func+"""\";
    DWORD cbWritten;
    DWORD dwBytesToWrite = (DWORD)strlen(buf);
    WriteFile(hPipe1, buf, dwBytesToWrite, &cbWritten, NULL);
    return """+func+"""();
    }"""
	print(onefunc)
	f = open(inpname+"_code.txt","a+")
	f.write("%s\r\n"%(onefunc))
	f.close()

	f2 = open(inpname+"_invoke.txt","a+")
	strinv = "perform_hook(TEXT(\"\"), \""+func+"\", Hook_"+func+");"
	f2.write("%s\r\n"%(strinv))
	f2.close()
	