//file: FloodFill.cpp

void floodFill(int x, int y, int target_color, int replacement_color)
{
	if (target_color!=replacement_color){
		
		// Get the pixel's color
		int node_color=getColor(x,y); //belom tau caranya
		

		if(node_color == target_color)
		{
			// Fill the pixel with the replacement_color
			// draw(blablabla)

			floodFill(x+1,y, target_color, replacement_color); //east
			floodFill(x-1,y, target_color, replacement_color); //west
			floodFill(x, y+1, target_color, replacement_color); //north
			floodFill(x,y-1, target_color, replacement_color); //south
		}
	}

}