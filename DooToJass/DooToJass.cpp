#include <Windows.h>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <String>

using namespace std;

#pragma pack(push,1)
struct w3eheader1
{
	char head[4];
	long version;
	char maintile;
	long iscustomtiles;
	long tilesets;
};
int cliffs;

struct w3eheader3
{
	long  Mx;
	long  My;
	float CX;
	float CY;
};

struct w3eDat
{
	short grheight; 
	short waterheight; 
	/*int flags:4;
	int groundtt:4;*/
	BYTE flagground;
	BYTE texturedet;
	/*int cliffttype:4;
	int layer:4;*/
	BYTE clifflay;
};

struct doodheader
{
	char head[4];
	long version;
	long subversion;
	long numbertrees;
};

struct dood
{
	char type[4];
	long variation;
	float x;
	float y;
	float z;
	float a;
	float xscale;
	float yscale;
	float zscale;
	BYTE flags;
	BYTE life;
	BYTE randtable[4];
	long dropc;
	long number;
};

struct dood7
{
	char type[4];
	long variation;
	float x;
	float y;
	float z;
	float a;
	float xscale;
	float yscale;
	float zscale;
	BYTE flags;
	BYTE life;
	long number;
};

struct charr
{
	char bf[4];
};
#pragma pack(pop)



int _tmain(int argc, _TCHAR* argv[])
{
	bool int_0 = 0 ,int_1 = 0,int_2 = 0, int_3 = 0, int_4 = 0, int_5 =0, int_6 =0, int_7 =0;
	string funcname,terrname;
	cout << "\nConvert war3map.doo to JASS?  1-yes 0-no:";
	cin >>int_0;

	if (int_0)
	{
	cout << "\nConvert war3map.doo to old version?  1-yes 0-no:";
	cin >>int_1;
	cout << "\nCreate \"function ... list ... endfunction\"?  1-yes 0-no:";
	cin >>int_2;
	if (int_2)
	{
			cout << "\nFuncName: ";
			cin >>funcname;
	}
	cout << "\nCreate empty war3map.doo?   1-yes 0-no:";
	cin >>int_3;
	BYTE tests = 0x13;
	printf( "\n%d %d", tests >> 4,tests & 15);
	cout << "\nCreate backup war3map.doo?   1-yes 0-no:";
	cin >>int_4;
	}
	cout << "\nConvert war3map.w3e to JASS?  1-yes 0-no:";
	cin >>int_5;
	if (int_5)
	{
	cout << "\nOnly textures?  1-yes 0-no:";
	cin >>int_6;
	if (int_6)
	{
	cout << "\nEnable filter?  1-yes 0-no:";
	cin >>int_7;
	if (int_7)
	{
		cout << "\nEnter filter(example:Ldrt):";
		cin >>terrname;
	}
	}
	}

		/* ------------------------------------------CONVERTER war3map.doo to JASS2 by Raichu--------------------------------------------------- */
	if (int_0)
	{
	if (int_4)
	{
	ifstream infile("war3map.doo", ios::binary);
    ofstream outfile("war3map.old", ios::binary);	
	outfile << infile.rdbuf();
	infile.close();
	outfile.close();
	}

	doodheader w3dohead,w3donullhead,w3doconvert;
	FILE *w3doo,*out, *fnull, *converted;
	/* open */
    w3doo = fopen("war3map.doo","rb");
	out = fopen("war3map.doo.j","w+");
	
	/* read head..*/
    fread(&w3dohead,sizeof(w3dohead),1,w3doo);
	/* write null-file */
	if (int_3)
	{
	fnull = fopen("war3mapNULL.doo","w+b");
	w3donullhead = w3dohead;
	w3donullhead.numbertrees = 0;
	fwrite(&w3donullhead,sizeof(w3donullhead),1,fnull);
	fclose(fnull);
	}
	if (int_1)
	{
	converted = fopen("war3mapCONV.doo","w+b");
	w3doconvert = w3dohead;
	if (w3dohead.version == 7)
		w3doconvert.version = 8;
	else
		w3doconvert.version = 7;
	fwrite(&w3doconvert,sizeof(w3doconvert),1,converted);
	}
	/* debug? */
	printf("\nFILE: %so\nVersion: %d.%d\nnumber:%d\n\n\n\n\n",w3dohead.head,w3dohead.version,w3dohead.subversion,w3dohead.numbertrees);
	/*Start functions*/
	fprintf_s(out, "function RF takes nothing returns nothing\ncall FogMaskEnable(false)\ncall FogEnable(false)\ncall FogMaskEnable(true)\ncall FogEnable(true)\nendfunction\n");
	fprintf_s(out, "function CD takes integer objectid, real x, real y, real z, real face, real scale, integer variation returns nothing\n");
	fprintf(out, "set bj_lastCreatedDestructable =  CreateDestructableZ(objectid,x,y,z,face,scale,variation)\nendfunction\n");
	fprintf_s(out, "function SL takes integer L returns nothing\n");
	fprintf(out, "call SetDestructableLife(GetLastCreatedDestructable(), GetDestructableMaxLife(GetLastCreatedDestructable()) * L * 0.01)\nendfunction\n\n\n\n\n\n\n\n");
	if (int_2)
	fprintf_s(out, "function %s takes nothing returns nothing\n",funcname.c_str());
	/* convert data to jass */
	for (int i = 0; i < w3dohead.numbertrees; i++)
	{

		if (w3dohead.version == 7)
		{
		dood7 w3do;
		dood w3doOLD;
		fread(&w3do,sizeof(dood7),1,w3doo);
		if (int_1)
		{
		/*start*/
		w3doOLD.a = w3do.a;
		w3doOLD.dropc = 0;
		w3doOLD.flags = w3do.flags;
		w3doOLD.life = w3do.life;
		w3doOLD.number = w3do.number;
		w3doOLD.randtable[0] = 0x00;
		w3doOLD.randtable[1] = 0x00;
		w3doOLD.randtable[2] = 0x00;
		w3doOLD.randtable[3] = 0x00;
		w3doOLD.randtable[4] = 0x00;
		w3doOLD.type[0] = w3do.type[0];
		w3doOLD.type[1] = w3do.type[1];
		w3doOLD.type[2] = w3do.type[2];
		w3doOLD.type[3] = w3do.type[3];
		w3doOLD.type[4] = w3do.type[4];
		w3doOLD.variation = w3do.variation;
		w3doOLD.x = w3do.x;
		w3doOLD.xscale = w3do.xscale;
		w3doOLD.y = w3do.y;
		w3doOLD.yscale = w3do.yscale;
		w3doOLD.z = w3do.z;
		w3doOLD.zscale = w3do.zscale;
		/*end*/
		fwrite(&w3doOLD,sizeof(dood),1,converted);
		}
		fprintf(out, "call CD( '%.4s', %g, %g, %g, %g, %g, %d )\n",w3do.type,w3do.x,w3do.y,w3do.z,w3do.a,w3do.zscale,w3do.variation);
		if (w3do.life < 100)
		fprintf_s(out,"call SL(%d)\n",w3do.life);
		}
		else
		{
		dood w3do;
		dood7 w3doOLD;
		fread(&w3do,sizeof(dood),1,w3doo);
		/*start*/
		if (int_1)
		{
		w3doOLD.a = w3do.a;
		w3doOLD.flags = w3do.flags;
		w3doOLD.life = w3do.life;
		w3doOLD.number = w3do.number;
		w3doOLD.type[0] = w3do.type[0];
		w3doOLD.type[1] = w3do.type[1];
		w3doOLD.type[2] = w3do.type[2];
		w3doOLD.type[3] = w3do.type[3];
		w3doOLD.type[4] = w3do.type[4];
		w3doOLD.variation = w3do.variation;
		w3doOLD.x = w3do.x;
		w3doOLD.xscale = w3do.xscale;
		w3doOLD.y = w3do.y;
		w3doOLD.yscale = w3do.yscale;
		w3doOLD.z = w3do.z;
		w3doOLD.zscale = w3do.zscale;
		/*end*/
		fwrite(&w3doOLD,sizeof(dood7),1,converted);
		}
		fprintf(out, "call CD( '%.4s', %.6g, %.6g, %.6g, %.6g, %.6g, %d )\n",w3do.type,w3do.x,w3do.y,w3do.z,w3do.a,w3do.zscale,w3do.variation);
		if (w3do.life < 100)
		fprintf_s(out,"call SL(%d)\n",w3do.life);
		}
	}
	fprintf_s(out,"call RF()");
	if (int_2)
	fprintf_s(out, "\nendfunction");
    fclose(w3doo);
	fclose(out);
	if (int_1)
	{
	fclose(converted);
	}
	system( "pause" );
	}
	if (int_5)
	{
	/* ------------------------------------------CONVERTER w3e to JASS2 by Raichu--------------------------------------------------- */
	w3eheader1 w3eData;
	FILE *w3ee,*out2;
	w3ee = fopen("war3map.w3e","rb");
	out2 = fopen("war3map.w3e.j","w+");
	fread(&w3eData,sizeof(w3eheader1),1,w3ee);
	printf_s("\nFILE: %.4s\n Version: %d\n Type:%c\n%d\n Tilesets(ground) %d\n",w3eData.head,w3eData.version,w3eData.maintile,w3eData.iscustomtiles,w3eData.tilesets);
	string *str2 = new string[w3eData.tilesets];
	fread(str2,4,w3eData.tilesets,w3ee);
	printf_s("List: %s\n",&str2[0]);
	fread(&cliffs,4,1,w3ee);
	printf_s("Tilesets(cliffs): %d\n",cliffs);
	string *str3 = new string[cliffs];
	fread(str3,4,cliffs,w3ee);
	printf_s("List: %s\n",&str3[0]);
	w3eheader3 w3eData2;
	fread(&w3eData2,sizeof(w3eheader3),1,w3ee);
	printf_s("\nCX: %f, CY: %f \n MX: %d, MY: %d \n \n \n %d",w3eData2.CX,w3eData2.CY,w3eData2.Mx,w3eData2.My, sizeof(w3eDat));
	int coordx=0,coordy=0;
	int maxx = w3eData2.Mx*w3eData2.My;
	int centerx = w3eData2.Mx/2 , centery = w3eData2.My /2;
	char tilesets_l[1024],cliffs_l[1024];
	sprintf(tilesets_l,"%s",&str2[0]);
	sprintf(cliffs_l,"%s",&str3[0]);
	
	for (int i = 0; i < maxx; i++)
	{
		w3eDat weedat;
		fread(&weedat,sizeof(w3eDat),1,w3ee);
		int groundtt = (weedat.flagground & 15)+1;
		int layer = weedat.clifflay & 15;
		if (!int_6 && ((((8192-weedat.grheight)/4)-(layer*128))+256) != 0)
		fprintf_s(out2,"call TerrainDeformCrater(%.2f, %.2f, 128, %d.00, 1, true)\n",(w3eData2.CX+coordx*128),(w3eData2.CY+coordy*128),(((8192-weedat.grheight)/4)-(layer*128))+256);
		if (!int_7)
		fprintf_s(out2,"call SetTerrainType(%.2f, %.2f, '%c%c%c%c', -1, 1, 1)\n",(w3eData2.CX+coordx*128),(w3eData2.CY+coordy*128),tilesets_l[groundtt*4-4],tilesets_l[groundtt*4-3],tilesets_l[groundtt*4-2],tilesets_l[groundtt*4-1]);
		else
		{
			char trlist[70];
			sprintf_s(trlist,"%c%c%c%c",tilesets_l[groundtt*4-4],tilesets_l[groundtt*4-3],tilesets_l[groundtt*4-2],tilesets_l[groundtt*4-1]);
			if (strcmp (trlist,terrname.c_str())==0)
			fprintf_s(out2,"call SetTerrainType(%.2f, %.2f, '%c%c%c%c', -1, 1, 1)\n",(w3eData2.CX+coordx*128),(w3eData2.CY+coordy*128),tilesets_l[groundtt*4-4],tilesets_l[groundtt*4-3],tilesets_l[groundtt*4-2],tilesets_l[groundtt*4-1]);
		}
		++coordx;
		if (coordx == w3eData2.Mx)
		{
		++coordy;
		coordx=0;
		}
	}
	fclose(w3ee);
	fclose(out2);

	system( "pause" );
	/*---END----*/
	}
	return 0;
}

