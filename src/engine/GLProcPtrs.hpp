/*I took this from the toast cat source code bc fuck writing this myself lmaoo*/

#pragma once
#include <gl/gl.h>
#include <gl/glext.h>

PFNGLCREATESHADERPROC             glCreateShader;
PFNGLCREATEPROGRAMPROC            glCreateProgram;
PFNGLSHADERSOURCEPROC				      glShaderSource;
PFNGLCOMPILESHADERPROC				    glCompileShader;
PFNGLGETSHADERIVPROC				      glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC			    glGetShaderInfoLog;
PFNGLATTACHSHADERPROC				      glAttachShader;
PFNGLLINKPROGRAMPROC				      glLinkProgram;
PFNGLGETPROGRAMIVPROC				      glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC			  glGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC				    glDeleteProgram;
PFNGLDETACHSHADERPROC				      glDetachShader;
PFNGLDELETESHADERPROC				      glDeleteShader;
PFNGLGENVERTEXARRAYSPROC			    glGenVertexArrays;
PFNGLGETUNIFORMLOCATIONPROC			  glGetUniformLocation;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC		  glVertexAttribPointer;
PFNGLDELETEVERTEXARRAYSPROC			  glDeleteVertexArrays;
PFNGLUSEPROGRAMPROC					      glUseProgram;
PFNGLBINDVERTEXARRAYPROC			    glBindVertexArray;
PFNGLUNIFORM1IPROC					      glUniform1i;

// Loaded in for shader use
PFNGLUNIFORM1FPROC					      glUniform1f;
PFNGLUNIFORM2FPROC					      glUniform2f;
PFNGLUNIFORM3FPROC					      glUniform3f;
PFNGLUNIFORM4FPROC					      glUniform4f;
PFNGLUNIFORMMATRIX4FVPROC				  glUniformMatrix4fv;

PFNGLUNIFORMMATRIX3FVPROC			    glUniformMatrix3fv;
PFNGLGENBUFFERSPROC					      glGenBuffers;
PFNGLDELETEBUFFERSPROC				    glDeleteBuffers;
PFNGLBUFFERDATAPROC					      glBufferData;
PFNGLBUFFERSUBDATAPROC				    glBufferSubData;
PFNGLBINDBUFFERPROC					      glBindBuffer;
PFNGLBLENDEQUATIONPROC				    glBlendEquation;
PFNGLACTIVETEXTUREPROC				    glActiveTexture;
PFNGLBINDATTRIBLOCATIONPROC       glBindAttribLocation;
PFNGLTEXIMAGE3DPROC               glTexImage3D;
