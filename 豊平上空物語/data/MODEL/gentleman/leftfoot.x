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
 70;
 0.00000;-0.08443;-0.04679;,
 0.93147;-0.32465;-1.74150;,
 0.00000;-0.32465;-2.44348;,
 0.00000;-0.08443;-0.04679;,
 1.31730;-0.32465;-0.04679;,
 0.00000;-0.08443;-0.04679;,
 0.93147;-0.32465;1.64793;,
 0.00000;-0.08443;-0.04679;,
 -0.00000;-0.32465;2.34990;,
 0.00000;-0.08443;-0.04679;,
 -0.93147;-0.32465;1.64793;,
 0.00000;-0.08443;-0.04679;,
 -1.31730;-0.32465;-0.04679;,
 0.00000;-0.08443;-0.04679;,
 -0.93147;-0.32465;-1.74150;,
 0.00000;-0.08443;-0.04679;,
 0.00000;-0.32465;-2.44348;,
 1.67845;-0.99774;-3.10056;,
 0.00000;-0.99774;-4.36547;,
 2.37369;-0.99774;-0.04679;,
 1.67845;-0.99774;3.00699;,
 -0.00000;-0.99774;4.27190;,
 -1.67845;-0.99774;3.00699;,
 -2.37369;-0.99774;-0.04679;,
 -1.67845;-0.99774;-3.10056;,
 0.00000;-0.99774;-4.36547;,
 2.09300;-1.97037;-3.85478;,
 0.00000;-1.97037;-5.43210;,
 2.95995;-1.97037;-0.04679;,
 2.09300;-1.97037;3.76121;,
 -0.00000;-1.97037;5.33853;,
 -2.09300;-1.97037;3.76121;,
 -2.95995;-1.97037;-0.04679;,
 -2.09300;-1.97037;-3.85478;,
 0.00000;-1.97037;-5.43210;,
 2.09300;-3.04991;-3.85478;,
 0.00000;-3.04991;-5.43210;,
 2.95995;-3.04991;-0.04679;,
 2.09300;-3.04991;3.76121;,
 -0.00000;-3.04991;5.33853;,
 -2.09300;-3.04991;3.76121;,
 -2.95995;-3.04991;-0.04679;,
 -2.09300;-3.04991;-3.85478;,
 0.00000;-3.04991;-5.43210;,
 1.67845;-4.02254;-3.10056;,
 0.00000;-4.02254;-4.36547;,
 2.37369;-4.02254;-0.04679;,
 1.67845;-4.02254;3.00699;,
 -0.00000;-4.02254;4.27190;,
 -1.67845;-4.02254;3.00699;,
 -2.37369;-4.02254;-0.04679;,
 -1.67845;-4.02254;-3.10056;,
 0.00000;-4.02254;-4.36547;,
 0.93147;-4.69563;-1.74150;,
 0.00000;-4.69563;-2.44348;,
 1.31730;-4.69563;-0.04679;,
 0.93147;-4.69563;1.64793;,
 -0.00000;-4.69563;2.34990;,
 -0.93147;-4.69563;1.64793;,
 -1.31730;-4.69563;-0.04679;,
 -0.93147;-4.69563;-1.74150;,
 0.00000;-4.69563;-2.44348;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;,
 0.00000;-4.93585;-0.04679;;
 
 56;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 3;54,53,62;,
 3;53,55,63;,
 3;55,56,64;,
 3;56,57,65;,
 3;57,58,66;,
 3;58,59,67;,
 3;59,60,68;,
 3;60,61,69;;
 
 MeshMaterialList {
  1;
  56;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  54;
  0.000000;1.000000;-0.000000;,
  0.000000;0.976601;-0.215059;,
  0.263162;0.953190;-0.148910;,
  0.364588;0.931169;-0.000000;,
  0.263162;0.953190;0.148909;,
  0.000000;0.976601;0.215059;,
  -0.263162;0.953190;0.148909;,
  -0.364588;0.931169;-0.000000;,
  -0.263162;0.953190;-0.148910;,
  0.000000;0.863074;-0.505077;,
  0.546617;0.771242;-0.326184;,
  0.714917;0.699209;-0.000000;,
  0.546616;0.771242;0.326183;,
  0.000000;0.863074;0.505077;,
  -0.546616;0.771242;0.326183;,
  -0.714917;0.699209;-0.000000;,
  -0.546617;0.771242;-0.326184;,
  0.243697;0.533550;-0.809899;,
  0.799677;0.324725;-0.505046;,
  0.963198;0.268795;-0.000000;,
  0.799677;0.324725;0.505045;,
  0.243697;0.533550;0.809899;,
  -0.799677;0.324725;0.505046;,
  -0.963198;0.268795;-0.000000;,
  -0.799677;0.324725;-0.505046;,
  0.563343;-0.351937;-0.747519;,
  0.799677;-0.324725;-0.505046;,
  0.963198;-0.268795;-0.000000;,
  0.799677;-0.324725;0.505046;,
  0.563343;-0.351937;0.747519;,
  -0.799677;-0.324725;0.505045;,
  -0.963198;-0.268795;-0.000000;,
  -0.799677;-0.324725;-0.505046;,
  0.000000;-0.863074;-0.505077;,
  0.546617;-0.771242;-0.326184;,
  0.714917;-0.699209;-0.000000;,
  0.546616;-0.771242;0.326183;,
  0.000000;-0.863074;0.505077;,
  -0.546616;-0.771242;0.326183;,
  -0.714917;-0.699209;-0.000000;,
  -0.546617;-0.771242;-0.326184;,
  0.000000;-0.976601;-0.215059;,
  0.263163;-0.953190;-0.148910;,
  0.364588;-0.931169;-0.000000;,
  0.263162;-0.953190;0.148909;,
  0.000000;-0.976601;0.215059;,
  -0.263162;-0.953190;0.148909;,
  -0.364588;-0.931169;-0.000000;,
  -0.263163;-0.953190;-0.148910;,
  -0.000000;-1.000000;-0.000000;,
  -0.601847;0.000000;0.798611;,
  -0.563343;-0.351937;0.747519;,
  -0.601847;0.000000;-0.798611;,
  -0.563343;-0.351937;-0.747519;;
  56;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;50,22,30,51;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,52,53,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;51,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,53,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  3;41,42,49;,
  3;42,43,49;,
  3;43,44,49;,
  3;44,45,49;,
  3;45,46,49;,
  3;46,47,49;,
  3;47,48,49;,
  3;48,41,49;;
 }
 MeshTextureCoords {
  70;
  0.062500;0.000000;,
  0.125000;0.142860;,
  0.000000;0.142860;,
  0.187500;0.000000;,
  0.250000;0.142860;,
  0.312500;0.000000;,
  0.375000;0.142860;,
  0.437500;0.000000;,
  0.500000;0.142860;,
  0.562500;0.000000;,
  0.625000;0.142860;,
  0.687500;0.000000;,
  0.750000;0.142860;,
  0.812500;0.000000;,
  0.875000;0.142860;,
  0.937500;0.000000;,
  1.000000;0.142860;,
  0.125000;0.285710;,
  0.000000;0.285710;,
  0.250000;0.285710;,
  0.375000;0.285710;,
  0.500000;0.285710;,
  0.625000;0.285710;,
  0.750000;0.285710;,
  0.875000;0.285710;,
  1.000000;0.285710;,
  0.125000;0.428570;,
  0.000000;0.428570;,
  0.250000;0.428570;,
  0.375000;0.428570;,
  0.500000;0.428570;,
  0.625000;0.428570;,
  0.750000;0.428570;,
  0.875000;0.428570;,
  1.000000;0.428570;,
  0.125000;0.571430;,
  0.000000;0.571430;,
  0.250000;0.571430;,
  0.375000;0.571430;,
  0.500000;0.571430;,
  0.625000;0.571430;,
  0.750000;0.571430;,
  0.875000;0.571430;,
  1.000000;0.571430;,
  0.125000;0.714290;,
  0.000000;0.714290;,
  0.250000;0.714290;,
  0.375000;0.714290;,
  0.500000;0.714290;,
  0.625000;0.714290;,
  0.750000;0.714290;,
  0.875000;0.714290;,
  1.000000;0.714290;,
  0.125000;0.857140;,
  0.000000;0.857140;,
  0.250000;0.857140;,
  0.375000;0.857140;,
  0.500000;0.857140;,
  0.625000;0.857140;,
  0.750000;0.857140;,
  0.875000;0.857140;,
  1.000000;0.857140;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
