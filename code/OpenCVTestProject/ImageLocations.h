#include <iostream>

std::string baseImagesPath[] = {
	"..\\images\\DSC_0566.jpg",
	"..\\images\\2715DTZ.jpg",
	"..\\images\\3028BYS.JPG",
	"..\\images\\3154FFY.JPG",
	"..\\images\\3266CNT.JPG",
	"..\\images\\3732FWW.JPG",
	"..\\images\\5445BSX.JPG",
	"..\\images\\7215BGN.JPG",
	"..\\images\\8995CCN.JPG",
	"..\\images\\9588DWV.jpg",
	"..\\images\\9773BNB.jpg",
	"..\\images\\DSC_0562.jpg"
};

std::string baseImagesName[] = {
	"DSC_0566",
	"2715DTZ",
	"3028BYS",
	"3154FFY",
	"3266CNT",
	"3732FWW",
	"5445BSX",
	"7215BGN",
	"8995CCN",
	"9588DWV",
	"9773BNB",
	"DSC_0562"
};

std::string positiveImagesPath[] = {
	"..\\images\\positive\\2715DTZ_0.jpg",
	"..\\images\\positive\\3028BYS_0.jpg",
	"..\\images\\positive\\3154FFY_0.jpg",
	"..\\images\\positive\\3266CNT_0.jpg",
	"..\\images\\positive\\3732FWW_0.jpg",
	"..\\images\\positive\\5445BSX_0.jpg",
	"..\\images\\positive\\7215BGN_0.jpg",
	"..\\images\\positive\\8995CCN_2.jpg",
	"..\\images\\positive\\8995CCN_3.jpg",
	"..\\images\\positive\\9588DWV_0.jpg",
	"..\\images\\positive\\DSC_0566_0.jpg",
	"..\\images\\positive\\DSC_0566_1.jpg"
};

std::string negativeImagesPath[] = {
	"..\\images\\negative\\2715DTZ_1.jpg",
	"..\\images\\negative\\2715DTZ_2.jpg",
	"..\\images\\negative\\3028BYS_1.jpg",
	"..\\images\\negative\\3154FFY_1.jpg",
	"..\\images\\negative\\3154FFY_2.jpg",
	"..\\images\\negative\\5445BSX_1.jpg",
	"..\\images\\negative\\7215BGN_1.jpg",
	"..\\images\\negative\\7215BGN_2.jpg",
	"..\\images\\negative\\8995CCN_0.jpg",
	"..\\images\\negative\\8995CCN_1.jpg",
	"..\\images\\negative\\8995CCN_4.jpg",
	"..\\images\\negative\\9588DWV_1.jpg",
	"..\\images\\negative\\9588DWV_2.jpg",
	"..\\images\\negative\\9588DWV_3.jpg",
	"..\\images\\negative\\9773BNB_0.jpg",
	"..\\images\\negative\\9773BNB_1.jpg",
	"..\\images\\negative\\DSC_0562_0.jpg",
	"..\\images\\negative\\DSC_0562_1.jpg",
	"..\\images\\negative\\DSC_0566_2.jpg"
};

std::string segmentImagesPath[] = {
	"..\\images\\segments\\3732FWW_0.jpg",
	"..\\images\\segments\\5445BSX_0.jpg",
	"..\\images\\segments\\5445BSX_1.jpg",
	"..\\images\\segments\\7215BGN_0.jpg",
	"..\\images\\segments\\7215BGN_1.jpg",
	"..\\images\\segments\\7215BGN_2.jpg",
	"..\\images\\segments\\8995CCN_0.jpg",
	"..\\images\\segments\\8995CCN_1.jpg",
	"..\\images\\segments\\8995CCN_2.jpg",
	"..\\images\\segments\\8995CCN_3.jpg",
	"..\\images\\segments\\8995CCN_4.jpg",
	"..\\images\\segments\\9588DWV_0.jpg",
	"..\\images\\segments\\9588DWV_1.jpg",
	"..\\images\\segments\\9588DWV_2.jpg",
	"..\\images\\segments\\9588DWV_3.jpg",
	"..\\images\\segments\\9773BNB_0.jpg",
	"..\\images\\segments\\9773BNB_1.jpg",
	"..\\images\\segments\\DSC_0562_0.jpg",
	"..\\images\\segments\\DSC_0562_1.jpg",
	"..\\images\\segments\\DSC_0566_0.jpg",
	"..\\images\\segments\\DSC_0566_1.jpg",
	"..\\images\\segments\\DSC_0566_2.jpg",
	"..\\images\\segments\\2715DTZ_0.jpg",
	"..\\images\\segments\\2715DTZ_1.jpg",
	"..\\images\\segments\\2715DTZ_2.jpg",
	"..\\images\\segments\\3028BYS_0.jpg",
	"..\\images\\segments\\3028BYS_1.jpg",
	"..\\images\\segments\\3154FFY_0.jpg",
	"..\\images\\segments\\3154FFY_1.jpg",
	"..\\images\\segments\\3154FFY_2.jpg",
	"..\\images\\segments\\3266CNT_0.jpg"
};


const int baseImagesAmount = 12;
const int positiveImagesAmount = 12;
const int negativeImagesAmount = 19;
const int segmentImagesAmount = 31;