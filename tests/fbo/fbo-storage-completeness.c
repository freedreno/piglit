/*
 * Copyright (c) 2011 VMware, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/*
 * @file fbo-storage-formats.c
 *
 * Tests if glRenderbufferStorage() affects framebuffer completeness.
 *
 * Author:
 *    Brian Paul
 *    Marek Olšák
 */

#include "piglit-util.h"
#include "piglit-framework.h"

int piglit_width = 100;
int piglit_height = 100;
int piglit_window_mode = GLUT_RGB;

static const char *TestName = "fbo-storage-formats";


static void
check_error(int line)
{
   GLenum err = glGetError();
   if (err) {
      printf("%s: Unexpected error 0x%x at line %d\n",
              TestName, err, line);
      piglit_report_result(PIGLIT_FAILURE);
   }
}


#define EXT_packed_depth_stencil 1
#define ARB_framebuffer_object 2
#define ARB_texture_rg 3
#define MAX_EXT 4

static GLboolean HaveExtension[MAX_EXT];



struct format_info
{
   GLenum format;
   GLuint extension;
};


static const struct format_info Formats[] = {
   { GL_RGB, 0 },
   { GL_R3_G3_B2, 0 },
   { GL_RGB4, 0 },
   { GL_RGB5, 0 },
   { GL_RGB8, 0 },
   { GL_RGB10, 0 },
   { GL_RGB12, 0 },
   { GL_RGB16, 0 },
   { GL_RGBA, 0 },
   { GL_RGBA2, 0 },
   { GL_RGBA4, 0 },
   { GL_RGB5_A1, 0 },
   { GL_RGBA8, 0 },
   { GL_RGB10_A2, 0 },
   { GL_RGBA12, 0 },
   { GL_RGBA16, 0 },
   { GL_STENCIL_INDEX, 0 },
   { GL_STENCIL_INDEX1_EXT, 0 },
   { GL_STENCIL_INDEX4_EXT, 0 },
   { GL_STENCIL_INDEX8_EXT, 0 },
   { GL_STENCIL_INDEX16_EXT, 0 },
   { GL_DEPTH_COMPONENT, 0 },
   { GL_DEPTH_COMPONENT16, 0 },
   { GL_DEPTH_COMPONENT24, 0 },
   { GL_DEPTH_COMPONENT32, 0 },

   /* GL_ARB_framebuffer_object additions */
   { GL_ALPHA, ARB_framebuffer_object },
   { GL_ALPHA4, ARB_framebuffer_object },
   { GL_ALPHA8, ARB_framebuffer_object },
   { GL_ALPHA12, ARB_framebuffer_object },
   { GL_ALPHA16, ARB_framebuffer_object },
   { GL_LUMINANCE_ALPHA, ARB_framebuffer_object },
   { GL_LUMINANCE, ARB_framebuffer_object },
   { GL_INTENSITY, ARB_framebuffer_object },

   /* GL_ARB_texture_rg */
   { GL_RED, ARB_texture_rg },
   { GL_R8, ARB_texture_rg },
   { GL_R16, ARB_texture_rg },
   { GL_RG, ARB_texture_rg },
   { GL_RG8, ARB_texture_rg },
   { GL_RG16, ARB_texture_rg },
#if 0
   /* XXX also depend on texture_float, texture_integer extensions */
   { GL_R16F, ARB_texture_rg },
   { GL_R32F, ARB_texture_rg },
   { GL_RG16F, ARB_texture_rg },
   { GL_RG32F, ARB_texture_rg },
   { GL_R8I, ARB_texture_rg },
   { GL_R8UI, ARB_texture_rg },
   { GL_R16I, ARB_texture_rg },
   { GL_R16UI, ARB_texture_rg },
   { GL_R32I, ARB_texture_rg },
   { GL_R32UI, ARB_texture_rg },
   { GL_RG8I, ARB_texture_rg },
   { GL_RG8UI, ARB_texture_rg },
   { GL_RG16I, ARB_texture_rg },
   { GL_RG16UI, ARB_texture_rg },
   { GL_RG32I, ARB_texture_rg },
   { GL_RG32UI, ARB_texture_rg },
#endif

   /* GL_EXT_packed_depth_stencil */
   { GL_DEPTH_STENCIL_EXT, EXT_packed_depth_stencil },
   { GL_DEPTH24_STENCIL8_EXT, EXT_packed_depth_stencil }
};


#define ELEMENTS(A) (sizeof(A) / sizeof(A[0]))


static enum piglit_result
test(void)
{
   GLuint fbo, rb;
   int i;
   int incomplete = -1, complete = -1;

   /* clear out any errors */
   while (glGetError())
      ;

   /* find a format which is incomplete */
   for (i = 0; i < ELEMENTS(Formats); i++) {
      if (!HaveExtension[Formats[i].extension])
          continue;

      glGenFramebuffersEXT(1, &fbo);
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
      check_error(__LINE__);

      glGenRenderbuffersEXT(1, &rb);
      check_error(__LINE__);
      glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb);

      glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
                                   GL_COLOR_ATTACHMENT0,
                                   GL_RENDERBUFFER_EXT,
                                   rb);
      check_error(__LINE__);

      glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, Formats[i].format,
                               piglit_width, piglit_height);
      if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT)
         complete = i;
      else
         incomplete = i;

      glDeleteFramebuffersEXT(1, &fbo);
      glDeleteRenderbuffersEXT(1, &rb);

      if (incomplete != -1 && complete != -1)
         break;
   }
   if (complete == -1) {
      printf("Found no renderbuffer format which is framebuffer complete.\n");
      return PIGLIT_FAIL;
   }
   if (incomplete == -1)
      return PIGLIT_PASS;

   glGenFramebuffersEXT(1, &fbo);
   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
   check_error(__LINE__);

   glGenRenderbuffersEXT(1, &rb);
   check_error(__LINE__);
   glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb);

   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
                                GL_COLOR_ATTACHMENT0,
                                GL_RENDERBUFFER_EXT,
                                rb);
   check_error(__LINE__);

   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, Formats[complete].format,
                            piglit_width, piglit_height);
   if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT) {
      printf("The format which was previously framebuffer complete is now incomplete.\n");
      return PIGLIT_FAIL;
   }

   glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, Formats[incomplete].format,
                            piglit_width, piglit_height);
   if (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE_EXT) {
      printf("The format which was previously framebuffer incomplete is now complete.\n");
      return PIGLIT_FAIL;
   }

   glDeleteFramebuffersEXT(1, &fbo);
   glDeleteRenderbuffersEXT(1, &rb);

   return PIGLIT_PASS;
}


enum piglit_result
piglit_display(void)
{
   return test();
}


void
piglit_init(int argc, char**argv)
{
   piglit_require_extension("GL_EXT_framebuffer_object");

   HaveExtension[0] = GL_TRUE;
   HaveExtension[EXT_packed_depth_stencil] = glutExtensionSupported("GL_EXT_packed_depth_stencil");
   HaveExtension[ARB_framebuffer_object] = glutExtensionSupported("GL_ARB_framebuffer_object");
   HaveExtension[ARB_texture_rg] = glutExtensionSupported("GL_ARB_texture_rg");

   piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);
}