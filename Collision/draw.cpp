/*************************************************************************
 * draw.cpp for project Collision
 * Author : lzh
 * Modifier : lzh Shlw lzh
 * Description : Source file to implement Object::Draw, which draws
 * objects in different coordinates of Object.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void Point::DrawVertex()
{
    glTexCoord2fv(glm::value_ptr(*vpTexture));
    glVertex4fv(glm::value_ptr(*vpCoordinate));
    return ;
}

void Triangle::Draw()
{
        pppVertex[0]->DrawVertex();
        pppVertex[1]->DrawVertex();
        pppVertex[2]->DrawVertex();
    return ;
}

void Model::Draw()
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < nLength; i++)
        tppCone[i]->Draw();
    glEnd();
    return ;
}

// Implementation of Object::Draw
void Object::Draw()
{
    // Switch to ModelView Matrix
    glMatrixMode(GL_MODELVIEW);

    // Save current matrix
    glPushMatrix();

    // Multiply mFrame to the right of current matrix in order to
    // transform coordinates in each Object to the global coordinates of
    // OpenGL.
    glMultMatrixf(glm::value_ptr(*mpFrame));
    
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, npTextureIndex[0]);
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
    
    // Draw Model
    mppModelList[nModelType]->Draw();
    
    glDisable(GL_TEXTURE_2D);
    
    // Restore matrix
    glPopMatrix();

    return ;
}

void Draw()
{
    for (int i = 0; i < nObjectTot; i++)
        oppObjectList[i]->Draw();
    return ;
}

void DrawBox()
{
    glDepthMask(GL_FALSE);
    glBegin(GL_LINES);
        glColor4f(0.7, 0.0, 0.0, 1.0);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[5]);
        glColor4f(0.0, 0.7, 0.0, 1.0);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[5]);
        glColor4f(0.0, 0.0, 0.7, 1.0);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[2], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[0], fpBoxLimit[3], fpBoxLimit[5]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[4]);
        glVertex3f(fpBoxLimit[1], fpBoxLimit[3], fpBoxLimit[5]);
    glEnd();
    glDepthMask(GL_TRUE);
    return ;
}

void DrawReadFiles(int argc, char* argv[])
{
    int t, s;
    char* cp = new char[501];
    FILE* f, * fi;
    struct jpeg_error_mgr jerr;
    struct jpeg_decompress_struct cinfo;
    JSAMPARRAY buffer = NULL;
    if (argc <= 1)
        f = fopen(cpTextureName, "r");
    else
        f = fopen(argv[1], "r");
    npPicWidth = new int[nTextureLength];
    npPicHeight = new int[nTextureLength];
    ucppPicContent = new unsigned char* [nTextureLength];
    npTextureIndex = new int[nTextureLength];
    cinfo.err = jpeg_std_error(&jerr);
    for (int i = 0; i < nTextureLength; i++)
    {
        fscanf(f, "%s", cp);
        fi = fopen(cp, "rb");
        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, fi);
        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);
        npPicWidth[i] = cinfo.output_width;
        npPicHeight[i] = cinfo.output_height;
        t = cinfo.output_width * cinfo.output_components;
        ucppPicContent[i] = new unsigned char[t * cinfo.output_height];
        buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, t, 1);
        while (cinfo.output_scanline < cinfo.output_height)
        {
            s = t * cinfo.output_scanline;
            jpeg_read_scanlines(&cinfo, buffer, 1);
            for (int j = 0; j < t; j++)
               ucppPicContent[i][s + j] = buffer[0][j];
        }
        fclose(fi);
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
    }
    delete cp;
    fclose(f);
    return ;
}

void DrawCreateTexture()
{
    for (int i = 0; i < nTextureLength; i++)
    {
        glGenTextures(1, (unsigned int*)(npTextureIndex+i));
        glBindTexture(GL_TEXTURE_2D, npTextureIndex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, npPicWidth[i], npPicHeight[i], 0, GL_RGB, GL_UNSIGNED_BYTE, ucppPicContent[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    return ;
}

void DrawCleanUp()
{
    for (int i = 0; i < nTextureLength; i++)
        delete ucppPicContent[i];
    delete npTextureIndex;
    delete npPicWidth, npPicWidth;
    delete ucppPicContent;
    return ;
}
