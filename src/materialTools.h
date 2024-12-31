#ifndef MATERIALTOOLS_H
#define MATERIALTOOLS_H

#include "ofMain.h"

enum Material {
	EMERALD,
	JADE,
	OBSIDIAN,
	PEARL,
	RUBY,
	TURQUOISE,
	BRASS,
	BRONZE,
	CHROME,
	COPPER,
	GOLD,
	SILVER,
	BLACK_PLASTIC,
	CYAN_PLASTIC,
	GREEN_PLASTIC,
	RED_PLASTIC,
	WHITE_PLASTIC,
	YELLOW_PLASTIC,
	ORANGE_RUBBER,
	PURPLE_RUBBER,
	YELLOW_TILE,
	BLUE_TILE,
	MAUVE_TILE,
	DARK_PURPLE_TILE,
	PINK_TILE,
	NONE
};

inline void setMaterial(Material material) {
	GLfloat  ambient[4], diffuse[4], specular[4];
	GLint coeffient = 0;

	switch (material) {
	case EMERALD:
		ambient[0] = 0.0215; ambient[1] = 0.1745; ambient[2] = 0.0215; ambient[3] = 1;
		diffuse[0] = 0.07568; diffuse[1] = 0.61424; diffuse[2] = 0.07568; diffuse[3] = 1;
		specular[0] = 0.633; specular[1] = 0.727811; specular[2] = 0.633; specular[3] = 1;
		coeffient = 0.6 * 128;
		break;

	case JADE:
		ambient[0] = 0.135; ambient[1] = 0.2225; ambient[2] = 0.1575; ambient[3] = 1;
		diffuse[0] = 0.54; diffuse[1] = 0.89; diffuse[2] = 0.63; diffuse[3] = 1;
		specular[0] = 0.316228; specular[1] = 0.316228; specular[2] = 0.316228; specular[3] = 1;
		coeffient = 0.1 * 128;
		break;

	case OBSIDIAN:
		ambient[0] = 0.05375; ambient[1] = 0.05; ambient[2] = 0.06625; ambient[3] = 1;
		diffuse[0] = 0.18275; diffuse[1] = 0.17; diffuse[2] = 0.22525; diffuse[3] = 1;
		specular[0] = 0.332741; specular[1] = 0.328634; specular[2] = 0.346435; specular[3] = 1;
		coeffient = 0.3 * 128;
		break;

	case PEARL:
		ambient[0] = 0.25; ambient[1] = 0.20725; ambient[2] = 0.20725; ambient[3] = 1;
		diffuse[0] = 1; diffuse[1] = 0.829; diffuse[2] = 0.829; diffuse[3] = 1;
		specular[0] = 0.296648; specular[1] = 0.296648; specular[2] = 0.296648; specular[3] = 1;
		coeffient = 0.088 * 128;
		break;

	case RUBY:
		ambient[0] = 0.1745; ambient[1] = 0.01175; ambient[2] = 0.01175; ambient[3] = 1;
		diffuse[0] = 0.61424; diffuse[1] = 0.04136; diffuse[2] = 0.04136; diffuse[3] = 1;
		specular[0] = 0.727811; specular[1] = 0.626959; specular[2] = 0.626959; specular[3] = 1;
		coeffient = 0.6 * 128;
		break;

	case TURQUOISE:
		ambient[0] = 0.1; ambient[1] = 0.18725; ambient[2] = 0.1745; ambient[3] = 1;
		diffuse[0] = 0.396; diffuse[1] = 0.74151; diffuse[2] = 0.69102; diffuse[3] = 1;
		specular[0] = 0.297254; specular[1] = 0.30829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.1 * 128;
		break;

	case BRASS:
		ambient[0] = 0.329412; ambient[1] = 0.223529; ambient[2] = 0.027451; ambient[3] = 1;
		diffuse[0] = 0.780392; diffuse[1] = 0.568627; diffuse[2] = 0.113725; diffuse[3] = 1;
		specular[0] = 0.992157; specular[1] = 0.941176; specular[2] = 0.807843; specular[3] = 1;
		coeffient = 0.21794872 * 128;
		break;

	case BRONZE:
		ambient[0] = 0.2125; ambient[1] = 0.1275; ambient[2] = 0.054; ambient[3] = 1;
		diffuse[0] = 0.714; diffuse[1] = 0.4284; diffuse[2] = 0.18144; diffuse[3] = 1;
		specular[0] = 0.393548; specular[1] = 0.271906; specular[2] = 0.166721; specular[3] = 1;
		coeffient = 0.2 * 128;
		break;

	case CHROME:
		ambient[0] = 0.25; ambient[1] = 0.25; ambient[2] = 0.25; ambient[3] = 1;
		diffuse[0] = 0.4; diffuse[1] = 0.4; diffuse[2] = 0.4; diffuse[3] = 1;
		specular[0] = 0.774597; specular[1] = 0.774597; specular[2] = 0.774597; specular[3] = 1;
		coeffient = 0.6 * 128;
		break;

	case COPPER:
		ambient[0] = 0.19125; ambient[1] = 0.0735; ambient[2] = 0.0225; ambient[3] = 1;
		diffuse[0] = 0.7038; diffuse[1] = 0.27048; diffuse[2] = 0.0828; diffuse[3] = 1;
		specular[0] = 0.256777; specular[1] = 0.137622; specular[2] = 0.086014; specular[3] = 1;
		coeffient = 0.1 * 128;
		break;

	case GOLD:
		ambient[0] = 0.24725; ambient[1] = 0.1995; ambient[2] = 0.0745; ambient[3] = 1;
		diffuse[0] = 0.75164; diffuse[1] = 0.60648; diffuse[2] = 0.22648; diffuse[3] = 1;
		specular[0] = 0.628281; specular[1] = 0.555802; specular[2] = 0.366065; specular[3] = 1;
		coeffient = 0.4 * 128;
		break;

	case SILVER:
		ambient[0] = 0.19225; ambient[1] = 0.19225; ambient[2] = 0.19225; ambient[3] = 1;
		diffuse[0] = 0.50754; diffuse[1] = 0.50754; diffuse[2] = 0.50754; diffuse[3] = 1;
		specular[0] = 0.508273; specular[1] = 0.508273; specular[2] = 0.508273; specular[3] = 1;
		coeffient = 0.4 * 128;
		break;

	case BLACK_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.01; diffuse[1] = 0.01; diffuse[2] = 0.01; diffuse[3] = 1;
		specular[0] = 0.50; specular[1] = 0.50; specular[2] = 0.50; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case CYAN_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.1; ambient[2] = 0.06; ambient[3] = 1;
		diffuse[0] = 0.0; diffuse[1] = 0.50980392; diffuse[2] = 0.50980392; diffuse[3] = 1;
		specular[0] = 0.50196078; specular[1] = 0.50196078; specular[2] = 0.50196078; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case GREEN_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.1; diffuse[1] = 0.35; diffuse[2] = 0.1; diffuse[3] = 1;
		specular[0] = 0.45; specular[1] = 0.55; specular[2] = 0.45; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case RED_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.5; diffuse[1] = 0.0; diffuse[2] = 0.0; diffuse[3] = 1;
		specular[0] = 0.7; specular[1] = 0.6; specular[2] = 0.6; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case WHITE_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.55; diffuse[1] = 0.55; diffuse[2] = 0.55; diffuse[3] = 1;
		specular[0] = 0.70; specular[1] = 0.70; specular[2] = 0.70; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case YELLOW_PLASTIC:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.5; diffuse[1] = 0.5; diffuse[2] = 0.0; diffuse[3] = 1;
		specular[0] = 0.60; specular[1] = 0.60; specular[2] = 0.50; specular[3] = 1;
		coeffient = 0.25 * 128;
		break;

	case ORANGE_RUBBER:
		ambient[0] = 0.745098039; ambient[1] = 0.301960784; ambient[2] = 0.117647059; ambient[3] = 1;
		diffuse[0] = 0.215686275; diffuse[1] = 0.152941176; diffuse[2] = 0.; diffuse[3] = 1;
		specular[0] = 0.066666667; specular[1] = 0.231372549; specular[2] = 0.019607843; specular[3] = 1;
		coeffient = 0.6 * 128;
		/*
		ambient[0] = 0.454; ambient[1] = 0.2392; ambient[2] = 0.0235; ambient[3] = 1;
		diffuse[0] = 0.8352; diffuse[1] = 0.4392; diffuse[2] = 0.0423; diffuse[3] = 1;
		specular[0] = 0.992157; specular[1] = 0.941176; specular[2] = 0.807843; specular[3] = 1;
		coeffient = 0.6 * 128;
		*/
		break;

	case PURPLE_RUBBER:
		ambient[0] = 0.105882353; ambient[1] = 0.039215686; ambient[2] = 0.121568627; ambient[3] = 1;
		diffuse[0] = 0.207843137; diffuse[1] = 0.078431373; diffuse[2] = 0.239215686; diffuse[3] = 1;
		specular[0] = 0.10829; specular[1] = 0.; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.6 * 128;
		break;

	case YELLOW_TILE:
		ambient[0] = 0.960784314; ambient[1] = 0.623529412; ambient[2] = 0.; ambient[3] = 1;
		diffuse[0] = 0.039215686; diffuse[1] = 0.098039216; diffuse[2] = 0.; diffuse[3] = 1;
		specular[0] = 0.3; specular[1] = 0.25; specular[2] = 0.; specular[3] = 1;
		coeffient = 0.2 * 128;
		/*
		ambient[0] = 0.454; ambient[1] = 0.2392; ambient[2] = 0.0235; ambient[3] = 1;
		diffuse[0] = 0.8352; diffuse[1] = 0.4392; diffuse[2] = 0.0423; diffuse[3] = 1;
		specular[0] = 0.3; specular[1] = 0.25; specular[2] = 0.05; specular[3] = 1;
		coeffient = 0.2 * 128;
		*/
		break;

	case BLUE_TILE:
		ambient[0] = 0.137254; ambient[1] = 0.262745; ambient[2] = 0.239215; ambient[3] = 1;
		diffuse[0] = 0.1921577; diffuse[1] = 0.3647; diffuse[2] = 0.33333; diffuse[3] = 1;
		specular[0] = 0.297254; specular[1] = 0.30829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.2 * 128;
		/*
		ambient[0] = 0.1607; ambient[1] = 0.3176; ambient[2] = 0.29019; ambient[3] = 1;
		diffuse[0] = 0.1608; diffuse[1] = 0.3218; diffuse[2] = 0.29412; diffuse[3] = 1;
		specular[0] = 0.297254; specular[1] = 0.30829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.2 * 128;
		*/
		break;

	case MAUVE_TILE:
		ambient[0] = 0.658; ambient[1] = 0.3019; ambient[2] = 0.4039; ambient[3] = 1;
		diffuse[0] = 0.11454; diffuse[1] = 0.2039; diffuse[2] = 0.17646; diffuse[3] = 1;
		specular[0] = 0.297254; specular[1] = 0.10829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.2 * 128;
		break;

	case DARK_PURPLE_TILE:
		ambient[0] = 0.11372; ambient[1] = 0.01568; ambient[2] = 0.3058; ambient[3] = 1;
		diffuse[0] = 0.08237; diffuse[1] = 0.01177; diffuse[2] = 0.227533; diffuse[3] = 1;
		specular[0] = 0.10829; specular[1] = 0.10829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.2 * 128;
		break;

	case PINK_TILE:
		ambient[0] = 0.96862; ambient[1] = 0.14901; ambient[2] = 0.50588; ambient[3] = 1;
		diffuse[0] = 0.011772; diffuse[1] = 0.30981; diffuse[2] = 0.180394; diffuse[3] = 1;
		specular[0] = 0.297254; specular[1] = 0.10829; specular[2] = 0.306678; specular[3] = 1;
		coeffient = 0.2 * 128;
		break;

	case NONE:
		ambient[0] = 1.0; ambient[1] = 1.0; ambient[2] = 1.0; ambient[3] = 1;
		diffuse[0] = 1.0; diffuse[1] = 1.0; diffuse[2] = 1.0; diffuse[3] = 1;
		specular[0] = 1.0; specular[1] = 1.0; specular[2] = 1.0; specular[3] = 1;
		coeffient = 128;
		break;

	default:
		ambient[0] = 0.0; ambient[1] = 0.0; ambient[2] = 0.0; ambient[3] = 1;
		diffuse[0] = 0.0; diffuse[1] = 0.0; diffuse[2] = 0.0; diffuse[3] = 1;
		specular[0] = 0.0; specular[1] = 0.0; specular[2] = 0.0; specular[3] = 1;
		coeffient = 0;
		break;
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, coeffient);
}

#endif // MATERIALTOOLS_H
