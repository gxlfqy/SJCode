//十进制到2至9进制的转换
int Ary(int nInput, int o)
{
	
	int result = 0;
	o = o < 2 || o > 9 ? 2 : o;
	while (nInput)
	{
		result *= 10;
		result += nInput % o;
		nInput /= o;
	}
	nInput = result;
	result = 0;
	while (nInput)
	{
		result *= 10;
		result += nInput % 10;
		nInput /= 10;
	}
	return result;
}
