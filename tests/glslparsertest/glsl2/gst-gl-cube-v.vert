// [config]
// expect_result: pass
// glsl_version: 1.10
// glsles_version: 1.00
//
// # NOTE: Config section was auto-generated from file
// # NOTE: 'glslparser.tests' at git revision
// # NOTE: 6cc17ae70b70d150aa1751f8e28db7b2a9bd50f0
// [end config]

/*
 * GStreamer
 * Copyright (C) 2008 Julien Isorce <julien.isorce@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* This shader appeared under #ifdef OPENGL_ES2, but looked interesting enough
 * to include in piglit anyway.
 */

attribute vec4 a_position;
attribute vec2 a_texCoord;
uniform mat4 u_matrix;
uniform float xrot_degree, yrot_degree, zrot_degree;
varying vec2 v_texCoord;
void main()
{
   float PI = 3.14159265;
   float xrot = xrot_degree*2.0*PI/360.0;
   float yrot = yrot_degree*2.0*PI/360.0;
   float zrot = zrot_degree*2.0*PI/360.0;
   mat4 matX = mat4 (
            1.0,        0.0,        0.0, 0.0,
            0.0,  cos(xrot),  sin(xrot), 0.0,
            0.0, -sin(xrot),  cos(xrot), 0.0,
            0.0,        0.0,        0.0, 1.0 );
   mat4 matY = mat4 (
      cos(yrot),        0.0, -sin(yrot), 0.0,
            0.0,        1.0,        0.0, 0.0,
      sin(yrot),        0.0,  cos(yrot), 0.0,
            0.0,        0.0,       0.0,  1.0 );
   mat4 matZ = mat4 (
      cos(zrot),  sin(zrot),        0.0, 0.0,
     -sin(zrot),  cos(zrot),        0.0, 0.0,
            0.0,        0.0,        1.0, 0.0,
            0.0,        0.0,        0.0, 1.0 );
   gl_Position = u_matrix * matZ * matY * matX * a_position;
   v_texCoord = a_texCoord;
}
