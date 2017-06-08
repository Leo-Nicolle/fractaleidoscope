/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Shader.cpp  -- Copyright (c) 2006 David Henry
// last modification: jan. 31, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Implementation of GLSL shader related classes.
//
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>

#include "Shader.h"

using std::cout;
using std::cerr;
using std::endl;


/////////////////////////////////////////////////////////////////////////////
//
// class Shader implementation.
//
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// Shader::Shader
//
// Constructor.
// --------------------------------------------------------------------------

Shader::Shader (const string &filename)
  : _name (filename), _handle (0), _compiled (0)
{
}


// --------------------------------------------------------------------------
// Shader::~Shader
//
// Destructor.  Destroy the shader handle.
// --------------------------------------------------------------------------

Shader::~Shader ()
{
  if (GLEW_VERSION_2_0)
    {
      if (glIsShader (_handle))
	glDeleteShader (_handle);
    }
  else if (GLEW_VERSION_1_5)
    {
      GLint type;
      glGetObjectParameterivARB (_handle, GL_OBJECT_TYPE_ARB, &type);

      if (type == GL_SHADER_OBJECT_ARB)
	glDeleteObjectARB (_handle);
    }
}


// -------------------------------------------------------------------------
// Shader::printInfoLog
//
// Print log info about a vertex or a fragment shader.
// -------------------------------------------------------------------------

void
Shader::printInfoLog () const
{
  GLint infologLength = 0;

  // First check for previous OpenGL errors...
  // checkOpenGLErrors ("Shader::printInfoLog (beginning)");

  // Get log's length
  if (GLEW_VERSION_2_0)
    {
      glGetShaderiv (_handle, GL_INFO_LOG_LENGTH, &infologLength);
    }
  else if (GLEW_VERSION_1_5)
    {
      glGetObjectParameterivARB (_handle, GL_OBJECT_INFO_LOG_LENGTH_ARB,
				 &infologLength);
    }

  // Print log if not empty
  if (infologLength > 1)
    {
      try
	{
	  GLchar *infoLog = new GLchar[infologLength];

	  // Get the log...
	  if (GLEW_VERSION_2_0)
	    glGetShaderInfoLog (_handle, infologLength, NULL, infoLog);
	  else if (GLEW_VERSION_1_5)
	    glGetInfoLogARB (_handle, infologLength, NULL, infoLog);

	  // ...and print it
	  cout << "Shader \"" << _name << "\" InfoLog ("
	       << infologLength << "):" << endl;
	  cout << infoLog << endl;

	  delete [] infoLog;
	}
      catch (std::bad_alloc &err)
	{
	  cerr << "Error: memory allocation failed for "
	       << "shader info log" << endl;
	  cerr << " Reason: " << err.what () << endl;
	}
    }

  // Last OpenGL error check (who said we are paranoiac?)
  // checkOpenGLErrors ("Shader::printInfoLog (end)");
}


// -------------------------------------------------------------------------
// Shader::compile
//
// Create and compile the shader.
// -------------------------------------------------------------------------

void
Shader::compile ()
  throw (std::runtime_error)
{
  const GLchar *code = _code.c_str ();

  if (GLEW_VERSION_2_0)
    {
      // Create a shader object
      _handle = glCreateShader (shaderType ());

      // Upload shader code to OpenGL
      glShaderSource (_handle, 1, &code, NULL);

      // Compile shader
      glCompileShader (_handle);
      glGetShaderiv (_handle, GL_COMPILE_STATUS, &_compiled);
      printInfoLog ();

      // Check for success
      if (GL_FALSE == _compiled)
	throw std::runtime_error ("Compilation failed");
    }
  else if (GLEW_VERSION_1_5)
    {
      // Create a shader object
      _handle = glCreateShaderObjectARB (shaderType ());

      // Upload shader code to OpenGL
      glShaderSourceARB (_handle, 1, &code, NULL);

      // Compile shader
      glCompileShaderARB (_handle);
      glGetObjectParameterivARB (_handle, GL_OBJECT_COMPILE_STATUS_ARB, &_compiled);
      printInfoLog ();

      // Check for success
      if (GL_FALSE == _compiled)
	throw std::runtime_error ("Compilation failed");
    }
}


// -------------------------------------------------------------------------
// Shader::loadShaderFile
//
// Load shader's GLSL code from file.  The code is stored into the
// _code string member variable.
// -------------------------------------------------------------------------

void
Shader::loadShaderFile (const string &filename)
  throw (std::runtime_error)
{
  // Open the file
  std::ifstream ifs (filename.c_str (), std::ios::in | std::ios::binary);

  if (ifs.fail ())
    throw std::runtime_error ("Couldn't open file");


  // Read whole file into string : short, efficient and standard... but doesnt work on VC++6.0 + shader compilation issues... 
  //_code.assign (std::istreambuf_iterator<char>(ifs),std::istreambuf_iterator<char>());


  //dirty working code by Yohan
  string line;
  int loc;

  while(!ifs.eof())	
  {
	  //read line by line
	  std::getline( ifs, line ); 
	  
	  //detect position of characters '/' '/' in the string
	  loc=line.find("//");
	  
	  //erase the rest of the string
	  if(loc>=0)
	  line.erase(line.begin()+loc, line.end());

	  //eventually append the cleaned line to the rest of the code of the shader	  
	  _code.append(line);
  }
   

  
  



  // Close file
  ifs.close ();
}


/////////////////////////////////////////////////////////////////////////////
//
// class VertexShader implementation.
//
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// VertexShader::VertexShader
//
// Constructor.  Read vertex shader code from file and compile it.
// --------------------------------------------------------------------------

VertexShader::VertexShader (const string &filename)
  : Shader (filename)
{
  try
    {
      // Load shader code from file
      loadShaderFile (filename);

      // Compile the shader
      compile ();

      cout << "* Vertex shader \"" << _name << "\" compiled" << endl;
    }
  catch (std::runtime_error &err)
    {
      cerr << "Error: Faild to create vertex shader from " << _name << endl;
      cerr << "Reason: " << err.what () << endl;
    }
}


/////////////////////////////////////////////////////////////////////////////
//
// class FragmentShader implementation.
//
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// FragmentShader::FragmentShader
//
// Constructor.  Read fragment shader code from file and compile it.
// --------------------------------------------------------------------------

FragmentShader::FragmentShader (const string &filename)
  : Shader (filename)
{
  try
    {
      // Load shader code from file
      loadShaderFile (filename);

      // Compile the shader
      compile ();

      cout << "* Fragment shader \"" << _name << "\" compiled" << endl;
    }
  catch (std::runtime_error &err)
    {
      cerr << "Error: Faild to create fragment shader from " << _name << endl;
      cerr << "Reason: " << err.what () << endl;
    }
}


/////////////////////////////////////////////////////////////////////////////
//
// class ShaderProgram implementation.
//
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// ShaderProgram::ShaderProgram
//
// Constructor.  Link vertex and fragment shader.  If the vertex shader
// or the fragment shader is invalid (has failed to compile), the
// shader program creation is aborted.
// --------------------------------------------------------------------------

ShaderProgram::ShaderProgram (const string &filename,
			      const VertexShader &vertexShader,
			      const FragmentShader &fragmentShader)
  : _name (filename), _handle (0), _linked (0)
{
  try
    {
      if (vertexShader.fail ())
	throw std::runtime_error ("Invalid vertex shader");

      if (fragmentShader.fail ())
	throw std::runtime_error ("Invalid fragment shader");

      if (GLEW_VERSION_2_0)
	{
	  // Create program and attach vertex and fragment shaders
	  _handle = glCreateProgram ();
	  glAttachShader (_handle, vertexShader.handle ());
	  glAttachShader (_handle, fragmentShader.handle ());

	  // Perform link stage
	  glLinkProgram (_handle);
	  glGetProgramiv (_handle, GL_LINK_STATUS, &_linked);

	  // Validate program
	  glValidateProgram (_handle);
	  printInfoLog ();

	  // Check for success
	  if (GL_FALSE == _linked)
	    throw std::runtime_error ("Link stage failed");
	}
      else if (GLEW_VERSION_1_5)
	{
	  // Create program and attach vertex and fragment shaders
	  _handle = glCreateProgramObjectARB ();
	  glAttachObjectARB (_handle, vertexShader.handle ());
	  glAttachObjectARB (_handle, fragmentShader.handle ());

	  // Perform link stage
	  glLinkProgramARB (_handle);
	  glGetObjectParameterivARB (_handle, GL_OBJECT_LINK_STATUS_ARB, &_linked);

	  // Validate program
	  glValidateProgramARB (_handle);
	  printInfoLog ();

	  // Check for success
	  if (GL_FALSE == _linked)
	    throw std::runtime_error ("Link stage failed");
	}

      cout << "* Shader \"" << _name << "\" successfully linked" << endl;
    }
  catch (std::runtime_error &err)
    {
      cerr << "Error: Faild to create shader " << _name << endl;
      cerr << "Reason: " << err.what () << endl;
    }
}


// --------------------------------------------------------------------------
// ShaderProgram::~ShaderProgram
//
// Destructor.  Destroy the shader program handle.
// --------------------------------------------------------------------------

ShaderProgram::~ShaderProgram ()
{
  if (GLEW_VERSION_2_0)
    {
      if (glIsProgram (_handle))
	glDeleteProgram (_handle);
    }
  else if (GLEW_VERSION_1_5)
    {
      GLint type;
      glGetObjectParameterivARB (_handle, GL_OBJECT_TYPE_ARB, &type);

      if (type == GL_PROGRAM_OBJECT_ARB)
	glDeleteObjectARB (_handle);
    }
}


// -------------------------------------------------------------------------
// ShaderProgram::use
// ShaderProgram::unuse
//
// Bind/unbind the shader.
// -------------------------------------------------------------------------

void
ShaderProgram::use () const
{
  if (GLEW_VERSION_2_0)
    {
      glUseProgram (_handle);
    }
  else if (GLEW_VERSION_1_5)
    {
      glUseProgramObjectARB (_handle);
    }
}


void
ShaderProgram::unuse () const
{
  if (GLEW_VERSION_2_0)
    {
      glUseProgram (0);
    }
  else if (GLEW_VERSION_1_5)
    {
      glUseProgramObjectARB (0);
    }
}


// -------------------------------------------------------------------------
// ShaderProgram::printInfoLog
//
// Print log info about a shader program.
// -------------------------------------------------------------------------

void
ShaderProgram::printInfoLog () const
{
  GLint infologLength = 0;

  // First check for previous OpenGL errors...
  // checkOpenGLErrors ("ShaderProgram::printInfoLog (beginning)");

  // Get log's length
  if (GLEW_VERSION_2_0)
    {
      glGetProgramiv (_handle, GL_INFO_LOG_LENGTH, &infologLength);
    }
  else if (GLEW_VERSION_1_5)
    {
      // Get log's length
      glGetObjectParameterivARB (_handle, GL_OBJECT_INFO_LOG_LENGTH_ARB,
				 &infologLength);
    }

  // Print log if not empty
  if (infologLength > 1)
    {
      try
	{
	  GLchar *infoLog = new GLchar[infologLength];

	  // Get the log...
	  if (GLEW_VERSION_2_0)
	    glGetProgramInfoLog (_handle, infologLength, NULL, infoLog);
	  else if (GLEW_VERSION_1_5)
	    glGetInfoLogARB (_handle, infologLength, NULL, infoLog);

	  // ...and print it
	  cout << "Program \"" << _name << "\" InfoLog ("
	       << infologLength << "):" << endl;
	  cout << infoLog << endl;

	  delete [] infoLog;
	}
      catch (std::bad_alloc &err)
	{
	  cerr << "Error: memory allocation failed for "
	       << "shader program info log" << endl;
	  cerr << " Reason: " << err.what () << endl;
	}
    }

  // Last OpenGL error check (who said we are paranoiac?)
  // checkOpenGLErrors ("Shader::printInfoLog (end)");
}
