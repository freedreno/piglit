// [config]
// expect_result: pass
// glsl_version: 1.40
// [end config]
#version 140

bool func()
{
	return gl_FrontFacing;
}
