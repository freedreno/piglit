// [config]
// expect_result: fail
// glsl_version: 1.00
// [end config]
//
// Type bool cannot have default precision.
//
// From section 4.5.3 of the GLSL 1.00 spec:
//     The precision statement
//         precision precision-qualifier type;
//     can be used to establish a default precision qualifier. The type field
//     can be either int or float. [...] Any other types or qualifiers will
//     result in an error.


#version 100

precision lowp bool;

float f() {
	return 0.0;
}
