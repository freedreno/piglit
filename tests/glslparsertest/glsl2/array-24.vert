// [config]
// expect_result: fail
// glsl_version: 1.10
// glsles_version: 1.00
// [end config]

void main()
{
    /* GLSL 1.10 4.1.9 Arrays
       Only one-dimensional arrays may be declared.
     */
    int a[1][2][3];

    gl_Position = gl_Vertex;
}
