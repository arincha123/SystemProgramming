#include <Windows.h>
#include "pch.h"

int CalculateMaterial(int productType, int materialType, int productQuantity, double param1, double param2)
{
    if (productQuantity <= 0 || param1 <= 0.0 || param2 <= 0.0) {
        return -1;
    }

    double productCoef = 0.0;

    switch (productType) {
    case 1: productCoef = 1.1; break;
    case 2: productCoef = 1.5; break;
    case 3: productCoef = 2.0; break;
    default: return -1; 
    }

    double scrapRate = 0.0;

    switch (materialType) {
    case 1: scrapRate = 0.003; break;
    case 2: scrapRate = 0.012; break;
    case 3: scrapRate = 0.050; break;
    default: return -1;
    }

    double materialPerUnit = param1 * param2 * productCoef;

    double totalPureMaterial = materialPerUnit * productQuantity;

    double totalWithScrap = totalPureMaterial / (1.0 - scrapRate);

    int finalMaterialCount = (int)totalWithScrap;
    if (totalWithScrap > finalMaterialCount) {
        finalMaterialCount++;
    }

    return finalMaterialCount;
}