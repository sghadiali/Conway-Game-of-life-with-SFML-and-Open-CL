bool get(__global bool *map, int x, int y, int w, int h, int gw, int gh)
{
    if( x < 0 || y < 0 || x >= w || y >= h ) return 0;
    else return map[y * w + x];
}

__kernel void devGolGenerate(__global bool *map_in, __global bool *map_out, int width, int height)
{
    int id = get_global_id(0);
    int x = id % height;
    int y = id / height;

    if(x >= width || y >= height) return;

    int idgw = get_global_size(0);
    int gw = idgw % height;
    int gh = idgw / height;
    int cell_count = 0;
    if(get(map_in, x-1, y-1, width, height, gw, gh)) ++cell_count;
    if(get(map_in, x-1, y  , width, height, gw, gh)) ++cell_count;
    if(get(map_in, x-1, y+1, width, height, gw, gh)) ++cell_count;
    if(get(map_in, x  , y-1, width, height, gw, gh)) ++cell_count;
    if(get(map_in, x  , y+1, width, height, gw, gh)) ++cell_count;
    if(get(map_in, x+1, y-1, width, height, gw, gh)) ++cell_count;
    if(get(map_in, x+1, y  , width, height, gw, gh)) ++cell_count;
    if(get(map_in, x+1, y+1, width, height, gw, gh)) ++cell_count;

    if(get(map_in, x, y, width, height, gw, gh) == 1 && (cell_count > 3 || cell_count < 2))
        map_out[ y * width + x ] = 0;
    else if(get(map_in, x, y, width, height, gw, gh) == 0 && cell_count == 3)
        map_out[ y * width + x ] = 1;
    else
        map_out[ y * width + x ] = get(map_in, x, y, width, height, gw, gh);    
}