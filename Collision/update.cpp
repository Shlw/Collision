/*************************************************************************
 * update.cpp for project Collision
 * Author : ymw
 * Modifier : ymw lzh lziad lzh
 * Description : Source file to implement functions about update and
 * collision detection.
 ************************************************************************/

// Inclusion of global header

#include "global.hpp"

// whether two objects are crashing or not
bool bpCrashing[100][100];
// faces each object shows
int npFaces[100];

bool collision_calc(PObject obj1, PModel mod1, PObject obj2, PModel mod2, 
            glm::dvec3 duang, glm::dvec3 c1, glm::dvec3 c2, glm::dvec3 n)
{
    n = n / glm::length(n); //I'm speechless.
    //needed: P(v), L(w), r
    glm::dvec3 rc1 = duang - c1;
    glm::dvec3 rc2 = duang - c2;//from c1 or c2 to duang
    glm::dmat3 I1 = glm::dmat3(*obj1 -> mpFrame) * 
            *mod1 -> mMomentOfInertia * 
            glm::transpose(glm::dmat3(*obj1 -> mpFrame));  //I(global) = A * I(model) * A^-1
    glm::dmat3 I2 = glm::dmat3(*obj2 -> mpFrame) *
            *mod2 -> mMomentOfInertia *
            glm::transpose(glm::dmat3(*obj2 -> mpFrame));
    glm::dvec3 w1 = *obj1 -> vpAngularMomentum * glm::inverse(I1);
    glm::dvec3 w2 = *obj2 -> vpAngularMomentum * glm::inverse(I2);
    glm::dvec3 v1_bef = *obj1 -> vpSpeed + glm::cross(w1, rc1);
    glm::dvec3 v2_bef = *obj2 -> vpSpeed + glm::cross(w2, rc2);
    double dv_bef = dot((v1_bef - v2_bef), n);
    if (dv_bef >= 0.0)
    {/*
        printf("c1 = %f,%f,%f\n", c1[0], c1[1], c1[2]);
        printf("c2 = %f,%f,%f\n", c2[0], c2[1], c2[2]);
        printf("duang = %f,%f,%f\n", duang[0], duang[1], duang[2]);
        printf("w1 = %f,%f,%f\n", w1[0], w1[1], w1[2]);
        printf("rc1 = %f,%f,%f\n", rc1[0], rc1[1], rc1[2]);
        printf("vc1 = %f,%f,%f\n", vc1[0], vc1[1], rc1[2]);
        printf("n = %f,%f,%f\n", n[0], n[1], n[2]);
        printf("rc2 = %f,%f,%f\n", rc2[0], rc2[1], rc2[2]);
        printf("vc2 = %f,%f,%f\n", vc2[0], vc2[1], rc2[2]);
        system("pause");*/
        return false;
    }
    double fenmu1 = glm::dot(
                    glm::cross(
                        glm::inverse(I1)*glm::cross(rc1, n),
                            rc1),
                            n) + 1.0 / mod1 -> dMass;
    double fenmu2 = glm::dot(
                    glm::cross(
                        glm::inverse(I2)*glm::cross(rc2, n),
                            rc2),
                            n) + 1.0 / mod2 -> dMass;
    double dP = (/*mod1 -> fElastic * mod2 -> fElastic*/1.0 + 1.0) * (dv_bef)
                    / (fenmu1 + fenmu2);
    *obj1 -> vpSpeed -= (dP / mod1 -> dMass)*n;
    *obj2 -> vpSpeed += (dP / mod2 -> dMass)*n;
    *obj1 -> vpAngularMomentum -= dP * glm::cross(rc1, n);
    *obj2 -> vpAngularMomentum += dP * glm::cross(rc2, n);
    return true;
}

bool collision_judge(PObject obj1, PObject obj2)
{
    bool flag = 0;
    PModel mod1 = mppModelList[obj1 -> nModelType];
    PModel mod2 = mppModelList[obj2 -> nModelType];
    double maxRad1 = mod1 -> dMaxRadius;
    double maxRad2 = mod2 -> dMaxRadius;
    glm::dvec4 zero4 = glm::dvec4(glm::dvec3(0.0), 1.0);
    glm::dvec4 ctemp;
    ctemp = *(obj1 -> mpFrame) * zero4;
    glm::dvec3 c1 = glm::dvec3(ctemp);
    ctemp = *(obj2 -> mpFrame) * zero4;
    glm::dvec3 c2 = glm::dvec3(ctemp);
    double l = glm::length(c1 - c2);
    PTriangle pside;
    if (l > maxRad1 + maxRad2) return 0;

    glm::dvec3 ic = (c2 - c1) / l;
    double nearest = 0.0;
    for (int i = 0; i < mod2 -> nLength; i++)
    for (int j = 0; j < 3; j++)
    {
        ctemp = *(obj2 -> mpFrame) *
            *(mod2 -> tppCone[i] -> pppVertex[j] -> vpCoordinate);
        glm::dvec3 temp(ctemp);
        if (glm::dot(temp - c2, ic) < nearest)
            nearest = glm::dot(temp - c2, ic);
    }
    l += nearest;
    for (int i = 0; i < mod1 -> nLength; i++)
    for (int j = 0; j < 3; j++)
    if (mod1 -> tppCone[i] -> pppVertex[j] -> nFlag)    //for each point
    {
        ctemp = *(obj1 -> mpFrame) *
            *(mod1 -> tppCone[i] -> pppVertex[j] -> vpCoordinate);
        glm::dvec3 temp(ctemp);     //collision: point
        if (glm::dot(temp - c1, ic) >= l)
        {
            glm::dvec3 wspeed = 
                glm::dmat3(*obj1 -> mpFrame) * 
                *mod1 -> mMomentOfInertia *
                glm::transpose(glm::dmat3(*obj1 -> mpFrame)) *
                *obj1 -> vpAngularMomentum;
            glm::dvec3 vpoint = glm::cross(wspeed, temp - c1) + *obj1 -> vpSpeed;
            pside =             //collision: triangle
                obj2 -> IsInside(&ctemp, &vpoint);
            if (pside != NULL)            //IsInside: true
            {
                if ( collision_calc(obj1, mod1, obj2, mod2, temp, c1, c2,
                            glm::dvec3(*pside -> vpNormalVector)
                        )       //moving closer: true
                   )
                // lzh : IsInside allocates memory, and you're supposed
                // to release it by hand.
                {
                    delete pside;
                    return true;
                }
                delete pside;
            }
        }
    }
    l = glm::length(c1 - c2);
    nearest = 0.0;
    for (int i = 0; i < mod1 -> nLength; i++)
    for (int j = 0; j < 3; j++)
    {
        ctemp = *(obj1 -> mpFrame) *
            *(mod1 -> tppCone[i] -> pppVertex[j] -> vpCoordinate);
        glm::dvec3 temp(ctemp);
        if (glm::dot(temp - c1, ic) > nearest)
            nearest = glm::dot(temp - c1, ic);
    }
    l -= nearest;
    for (int i = 0; i < mod2 -> nLength; i++)
    for (int j = 0; j < 3; j++)
    if (mod2 -> tppCone[i] -> pppVertex[j] -> nFlag)    //for each point
    {
        ctemp = *(obj2 -> mpFrame) *
            *(mod2 -> tppCone[i] -> pppVertex[j] -> vpCoordinate);
        glm::dvec3 temp(ctemp);     //collision: point
        if (glm::dot(temp - c2, ic) <= -l)
        {
            /*glm::dvec3 wspeed = 
                glm::dmat3(*obj2 -> mpFrame) * 
                *mod2 -> mMomentOfInertia *
                glm::transpose(glm::dmat3(*obj2 -> mpFrame)) *
                *obj2 -> vpAngularMomentum;*/
            glm::dvec3 vpoint/* = glm::cross(wspeed, temp - c1) + *obj2 -> vpSpeed*/;
            pside =             //collision: triangle
                obj1 -> IsInside(&ctemp, &vpoint);
            if (pside != NULL)            //IsInside: true
            {
                if ( collision_calc(obj2, mod2, obj1, mod1, temp, c2, c1,
                            glm::dvec3(*pside -> vpNormalVector)
                        )       //moving closer: true
                   )
                // lzh : IsInside allocates memory, and you're supposed
                // to release it by hand.
                {
                    delete pside;
                    return true;
                }
                delete pside;
            }
        }
    }
    return false;
}

void Update()
{
    double dt = dLastClock - dLastLastClock;
    bool judged[nObjectTot];
    const double fEpsilon = 1.0E-7;
    memset(judged, false, sizeof(nObjectTot));
    for (int i = 0; i < nObjectTot; i++)
    {
        if (judged[i]) continue;
        for (int j = i + 1; j < nObjectTot; j++)
            if (judged[j]) continue;
            else if (collision_judge(oppObjectList[i], oppObjectList[j]))
            {
                judged[i] = judged[j] = true;
                
                // only play sounds for once
                // when bpCrashing[i][j] turns from false to true
                if (!bpCrashing[i][j]) {
                    if (nSndFileCount)
                        // play a random wav file
                        Audio::GetAudio()->LoadFile(rand() % nSndFileCount);
                    ++npFaces[i]; ++npFaces[j];
                    if (npFaces[i] == nTextureLength) npFaces[i] = 0;
                    if (npFaces[j] == nTextureLength) npFaces[j] = 0;
                }
                bpCrashing[i][j] = true;
            }
            else
                bpCrashing[i][j] = false;
    }
    for (int i = 0; i < nObjectTot; i++)
    {
        PObject pobji = oppObjectList[i];
        PModel  pmodi = mppModelList[pobji -> nModelType];
        PMat4 pframe = pobji -> mpFrame;
        PVec3 pspeed = pobji -> vpSpeed;
        (*pframe)[3] = glm::translate
            (glm::dmat4(1.0), (*pspeed)*dt) * (*pframe)[3];
        glm::dmat3 frame(*pframe);
        glm::dmat3 I = (frame)*(*pmodi -> mMomentOfInertia)*(glm::transpose(frame));
        glm::dvec3 omega = glm::inverse(I) * *pobji -> vpAngularMomentum;
        if (glm::length(omega) > fEpsilon)
        {
            double x = (*pframe)[3][0]; (*pframe)[3][0] = .0;
            double y = (*pframe)[3][1]; (*pframe)[3][1] = .0;
            double z = (*pframe)[3][2]; (*pframe)[3][2] = .0;
            (*pframe) = glm::rotate(glm::dmat4(1.0), glm::length(omega)*dt, omega/glm::length(omega)) * (*pframe) ;
            (*pframe)[3][0] = x;
            (*pframe)[3][1] = y;
            (*pframe)[3][2] = z;
            (*pframe)[3][3] = 1.0;
        }
    // (*pobji -> vpAngularMomentum) = glm::dvec3(glm::rotate(glm::ddmat4(1.0), glm::length(omega)*dt, omega/glm::length(omega)) * glm::dvec4(*pobji -> vpAngularMomentum, 1.0));
    /*
    (*pframe)[0] /= glm::length((*pframe)[0]);
    (*pframe)[1] -= (*pframe)[0]*glm::dot((*pframe)[0], (*pframe)[1]);
    (*pframe)[1] /= glm::length((*pframe)[1]);
    (*pframe)[2] -= (*pframe)[0]*glm::dot((*pframe)[0], (*pframe)[2]);
    (*pframe)[2] -= (*pframe)[1]*glm::dot((*pframe)[1], (*pframe)[2]);
    (*pframe)[2] /= glm::length((*pframe)[2]);
    (*pframe)[3][3] = 1.0;
    */
    if ((*pframe)[3][0] < dpBoxLimit[0])
        (*pspeed)[0] = fabs((*pspeed)[0]);
    if ((*pframe)[3][0] > dpBoxLimit[1])
        (*pspeed)[0] = -fabs((*pspeed)[0]);
    if ((*pframe)[3][1] < dpBoxLimit[2])
        (*pspeed)[1] = fabs((*pspeed)[1]);
    if ((*pframe)[3][1] > dpBoxLimit[3])
        (*pspeed)[1] = -fabs((*pspeed)[1]);
    if ((*pframe)[3][2] < dpBoxLimit[4])
        (*pspeed)[2] = fabs((*pspeed)[2]);
    if ((*pframe)[3][2] > dpBoxLimit[5])
        (*pspeed)[2] = -fabs((*pspeed)[2]);

    }
    return ;
}
