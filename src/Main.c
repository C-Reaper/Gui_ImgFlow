#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"


Sprite input;
Sprite target;
Sprite output;

Vec2* tar;
Vec2* flow;
char* lock;

void CalcTargets(){
    memset(tar,0,sizeof(Vec2) * input.w * input.h);
	memset(flow,0,sizeof(Vec2) * input.w * input.h);
	memset(lock,0,sizeof(char) * input.w * input.h);

	for(int i = 0;i<input.w * input.h;i++){
		const Pixel c = input.img[i];
		float nearest = INFINITY;
		int nearest_p = 0;

		for(int j = 0;j<target.w * target.h;j++){
			if(lock[j]) continue;

			const Pixel o = target.img[j];
			const float d = Pixel_DistF(c,o);
			if(d < nearest){
				nearest = d;
				nearest_p = j;
			}
		}

		lock[nearest_p] = 1;
		flow[i] = (Vec2){ i % input.w,i / input.w };
		tar[i] = (Vec2){ nearest_p % target.w,nearest_p / target.w };
	}
}

void Setup(AlxWindow* w){
	input = Sprite_Load("./assets/Kali_125.png");
	target = Sprite_Load("./assets/Arch_125.png");
	output = Sprite_New(input.w,input.h);

	tar = (Vec2*)malloc(sizeof(Vec2) * input.w * input.h);
	flow = (Vec2*)malloc(sizeof(Vec2) * input.w * input.h);
	lock = (char*)malloc(sizeof(char) * input.w * input.h);
}
void Update(AlxWindow* w){
    if(Stroke(ALX_MOUSE_L).DOWN){
		CalcTargets();
	}
	
	Clear(BLACK);

	for(int i = 0;i<input.w * input.h;i++){
		Vec2* p = flow + i;
		const Vec2 t = tar[i];
		const Vec2 d = Vec2_Sub(t,*p);
		*p = Vec2_Add(*p,Vec2_Mulf(d,0.0025f));
		if(p->x < 0.0f || p->x >= output.w || p->y < 0.0f || p->y >= output.h)
			continue;

		const Pixel c = input.img[i];
		output.img[(int)p->y * output.w + (int)p->x] = c;
	}

	Sprite_RenderAlpha(WINDOW_STD_ARGS,&input,0.0f,0.0f);
	Sprite_RenderAlpha(WINDOW_STD_ARGS,&output,input.w,0.0f);
}
void Delete(AlxWindow* w){
    Sprite_Free(&input);
    Sprite_Free(&target);
    Sprite_Free(&output);

	if(tar) free(tar);
	tar = NULL;

	if(flow) free(flow);
	flow = NULL;

	if(lock) free(lock);
	lock = NULL;
}

int main(){
    if(Create("Img Flow",250,125,8,8,Setup,Update,Delete))
        Start();
    return 0;
}