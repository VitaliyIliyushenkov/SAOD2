void string_copy(char* d, char* s) {
	for (char* pd = d, *ps = s; *pd++ = *ps++;);
}

int len(const char* s) {
	return sizeof(s);
}
int compare(const char* s, const char* t) {
	if (len(s) > len(t)) return 1;
	if (len(s) < len(t)) return -1;
	else return 0;
}