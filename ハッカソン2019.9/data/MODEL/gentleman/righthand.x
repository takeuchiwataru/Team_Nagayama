xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 17;
 -0.08218;1.06243;3.84569;,
 -8.39605;-0.18759;-0.11885;,
 -0.08218;-3.57181;2.29510;,
 -8.39605;-0.18759;-0.11885;,
 -0.08218;-3.52916;-2.59149;,
 -8.39605;-0.18759;-0.11885;,
 -0.08218;1.13143;-4.06097;,
 -8.39605;-0.18759;-0.11885;,
 -0.08218;3.96918;-0.08257;,
 -8.39605;-0.18759;-0.11885;,
 -0.08218;1.06243;3.84569;,
 -0.08218;-0.18759;-0.11885;,
 -0.08218;1.06243;3.84569;,
 -0.08218;-3.57181;2.29510;,
 -0.08218;-3.52916;-2.59149;,
 -0.08218;1.13143;-4.06097;,
 -0.08218;3.96918;-0.08257;;
 
 10;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;11,12,13;,
 3;11,13,14;,
 3;11,14,15;,
 3;11,15,16;,
 3;11,16,12;;
 
 MeshMaterialList {
  1;
  10;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.611765;0.602353;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  6;
  -0.374991;-0.294150;0.879123;,
  -0.374991;-0.926993;-0.008091;,
  -0.374991;-0.278763;-0.884123;,
  -0.374991;0.754710;-0.538326;,
  1.000000;0.000000;0.000000;,
  -0.374991;0.745198;0.551417;;
  10;
  3;0,0,0;,
  3;1,1,1;,
  3;2,2,2;,
  3;3,3,3;,
  3;5,5,5;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;;
 }
 MeshTextureCoords {
  17;
  0.000000;1.000000;,
  0.100000;0.000000;,
  0.200000;1.000000;,
  0.200000;0.000000;,
  0.400000;1.000000;,
  0.300000;0.000000;,
  0.600000;1.000000;,
  0.400000;0.000000;,
  0.800000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
