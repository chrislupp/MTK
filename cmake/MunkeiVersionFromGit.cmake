# The MIT License (MIT)
#
# Copyright (c) 2016 Theo Willows
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Heavily modified by Zi Yang Pang to retrieve git-hash instead of tags

cmake_minimum_required( VERSION 3.0.0 )

include( CMakeParseArguments )

function( version_from_git )
  # Parse arguments
  set( options OPTIONAL FAST )
  set( oneValueArgs
    GIT_EXECUTABLE
    INCLUDE_HASH
    LOG
    TIMESTAMP
  )
  set( multiValueArgs )
  cmake_parse_arguments( ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  # Defaults
  if( NOT DEFINED ARG_INCLUDE_HASH )
    set( ARG_INCLUDE_HASH ON )
  endif()

  if( DEFINED ARG_GIT_EXECUTABLE )
    set( GIT_EXECUTABLE "${ARG_GIT_EXECUTABLE}" )
  else ()
    # Find Git or bail out
    find_package( Git )
    if( NOT GIT_FOUND )
      message( WARNING "Git not found, setting Git Hash/Tag to Unknown" )
      set( GIT_HASH      "Unknown"     PARENT_SCOPE )
      set( GIT_TAG       "Unknown"     PARENT_SCOPE )
      return()
    endif( NOT GIT_FOUND )
  endif()
  
  # Git describe tag
  execute_process(
    COMMAND           "${GIT_EXECUTABLE}" describe --tags
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE   git_result
    OUTPUT_VARIABLE   git_tag
    ERROR_VARIABLE    git_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )

  # Git rev-parse
  execute_process(
    COMMAND           "${GIT_EXECUTABLE}" rev-parse HEAD
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE   git_result
    OUTPUT_VARIABLE   git_hash
    ERROR_VARIABLE    git_error
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
  )

  # Log the results
  if( ARG_LOG )
    message( STATUS
      "[MunkeiVersionFromGit] Version: ${version}
     Git hash:    [${git_hash}]
     Git tag      [${git_tag}] "
    )
  endif( ARG_LOG )
  
  #check if code is exactly at a tag
  if(NOT git_tag MATCHES "^v(0|[1-9][0-9]*)[.](0|[1-9][0-9]*)[.](0|[1-9][0-9]*)" )
    message( STATUS
      "[MunkeiVersionFromGit] Current code is not exactly at a tag" )
    set( git_tag       "Not at a tag" )
  endif()

  # Set parent scope variables
  set( GIT_HASH      ${git_hash}      PARENT_SCOPE )
  set( GIT_TAG       ${git_tag}       PARENT_SCOPE )

endfunction( version_from_git )