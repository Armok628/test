#include <stdio.h>
#include "aterm.h"

int main(int argc, char **argv)
{
	int size = 50;
	if (argc > 1)
		sscanf(argv[1], "%d", &size);

	printf(CLS CUP("0","0"));

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			// Translated from https://codepen.io/Artemiy_Aka/pen/jWrdOR
			int red   = 255 - ((float)x / size) * 255;
			int green = 255 - ((float)y / size) * 255;
			int blue  =       ((float)x / size) * 255;
			printf(SGR(BG_COLR(CUSTOM RGB("%d","%d","%d"))) "  ",
					red, green, blue);
		}
		printf(SGR(RESET) "\n");
	}

	printf(SGR(RESET) CUP("%d","1"), size + 2);
}
