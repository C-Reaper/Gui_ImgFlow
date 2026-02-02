#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"


Sprite input;
Sprite target;

Vec2* tar;
Vec2* flow;

void CalcTargets(){
    memset(tar,0,sizeof(Vec2) * input.w * input.h);
	memset(flow,0,sizeof(Vec2) * input.w * input.h);

	for(int i = 0;i<input.w * input.h;i++){
		const Pixel c = input.img[i];
		float nearest = 1.0f;
		Vec2 nearest_p = { 0.0f,0.0f };

		for(int j = 0;j<target.w * target.h;j++){
			const Pixel o = target.img[j];
			const float d = Pixel_DistF(c,o);
			if(d < nearest){
				nearest = d;
				nearest_p = (Vec2){ j % target.w,j / target.w };
			}
		}

		flow[i] = (Vec2){ i % input.w,i / input.w };
		tar[i] = nearest_p;
	}
}

void Setup(AlxWindow* w){
	input = Sprite_Load("./assets/Mario_l.png");
	target = Sprite_Load("./assets/Mario_r.png");

	tar = (Vec2*)malloc(sizeof(Vec2) * input.w * input.h);
	flow = (Vec2*)malloc(sizeof(Vec2) * input.w * input.h);

	CalcTargets();
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
		*p = Vec2_Add(*p,Vec2_Mulf(d,0.1f));
		
		const Pixel c = input.img[i];
		target.img[(int)p->y * target.w + (int)p->x] = c;
	}

	Sprite_Render(WINDOW_STD_ARGS,&input,0.0f,0.0f);
	Sprite_Render(WINDOW_STD_ARGS,&target,input.w,0.0f);
}
void Delete(AlxWindow* w){
    Sprite_Free(&input);
    Sprite_Free(&target);

	if(tar) free(tar);
	tar = NULL;

	if(flow) free(flow);
	flow = NULL;
}

int main(){
    if(Create("Img Flow",2500,1250,1,1,Setup,Update,Delete))
        Start();
    return 0;
}