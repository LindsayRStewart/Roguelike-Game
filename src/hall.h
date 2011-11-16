#ifndef HALL_H
#define HALL_H	
	
#include "base_room.h"
	
class hall: public base_room {
	public:	
		hall(int newid, int newx, int newy, base_room* origin);
		bool Expand(tile LayerMap[][HEIGHT]);
		void Place_Doors(tile LayerMap[][HEIGHT], int& nhalls, int nrooms);
		void Build_Connections(tile LayerMap[][HEIGHT], tree* ConTree, node* parent);
		void Light_Room(tile LayerMap[][HEIGHT]);
		void Darken_Room(tile LayerMap[][HEIGHT]);
	private:
		int h_length;
		int end_x;
		int end_y;
		int inc_x;
		int inc_y;
		base_room* origin_room;
		base_room* final_room;
};

#endif
