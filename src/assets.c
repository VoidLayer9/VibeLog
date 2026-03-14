#include "assets.h"

app_embedded_asset embedded_assets[] = {
{
.path = "meta.json",
 .content = (unsigned char[]){123,10,32,32,32,32,34,118,101,114,115,105,111,110,34,58,32,34,48,46,48,46,49,48,34,10,125,},
 .size = 27,
 .is_binary = 0
},
};

unsigned long embedded_assets_total_size = 1;
