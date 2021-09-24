#include <cinnabar-render/types.hpp>

#include <GL/glew.h>

const ce::BufferBit
	ce::COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT,
	ce::DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT,
	ce::STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT;

const ce::DepthFunc
	ce::DEPTH_NEVER = GL_NEVER,
	ce::DEPTH_LESS = GL_LESS,
	ce::DEPTH_EQUAL = GL_EQUAL,
	ce::DEPTH_LEQUAL = GL_LEQUAL,
	ce::DEPTH_GREATER = GL_GREATER,
	ce::DEPTH_NOTEQUAL = GL_NOTEQUAL,
	ce::DEPTH_GEQUAL = GL_GEQUAL,
	ce::DEPTH_ALWAYS = GL_ALWAYS;

const ce::Datatype
	TYPE_BYTE = GL_BYTE,
	TYPE_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	TYPE_SHORT = GL_SHORT,
	TYPE_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	TYPE_INT = GL_INT,
	TYPE_UNSIGNED_INT = GL_UNSIGNED_INT,

	TYPE_HALF_FLOAT = GL_HALF_FLOAT,
	TYPE_FLOAT = GL_FLOAT,
	TYPE_DOUBLE = GL_DOUBLE,

	TYPE_FIXED = GL_FIXED,

	TYPE_INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
	TYPE_UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,

	TYPE_UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
	TYPE_UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
	TYPE_UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
	TYPE_UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
	TYPE_UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
	TYPE_UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
	TYPE_UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
	TYPE_UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
	TYPE_UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
	TYPE_UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
	TYPE_UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
	TYPE_UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV;

const ce::TextureTarget
	TARGET_TEXTURE_2D = GL_TEXTURE_2D,
	TARGET_PROXY_TEXTURE_2D = GL_PROXY_TEXTURE_2D,
	TARGET_TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TARGET_PROXY_TEXTURE_1D_ARRAY = GL_PROXY_TEXTURE_1D_ARRAY,
	TARGET_TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
	TARGET_PROXY_TEXTURE_RECTANGLE = GL_PROXY_TEXTURE_RECTANGLE,
	TARGET_TEXTURE_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	TARGET_TEXTURE_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	TARGET_TEXTURE_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	TARGET_TEXTURE_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	TARGET_TEXTURE_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	TARGET_TEXTURE_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
	TARGET_PROXY_TEXTURE_CUBE_MAP = GL_PROXY_TEXTURE_CUBE_MAP;

const ce::Meshformat
	MESHFORMAT_POINTS = GL_POINTS,
	MESHFORMAT_LINE_STRIP = GL_LINE_STRIP,
	MESHFORMAT_LINE_LOOP = GL_LINE_LOOP,
	MESHFORMAT_LINES = GL_LINES,
	MESHFORMAT_LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	MESHFORMAT_LINES_ADJACENCY = GL_LINES_ADJACENCY,
	MESHFORMAT_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	MESHFORMAT_TRIANGLE_FAN = GL_TRIANGLE_FAN,
	MESHFORMAT_TRIANGLES = GL_TRIANGLES,
	MESHFORMAT_TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	MESHFORMAT_TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	MESHFORMAT_PATCHES = GL_PATCHES;