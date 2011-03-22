/******************************************************************************
Copyright (c) 2010, Google Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the <ORGANIZATION> nor the names of its contributors 
    may be used to endorse or promote products derived from this software 
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#pragma once
#include "ipfw.h"

class WptDriverCore {
public:
  WptDriverCore(WptStatus &status);
  ~WptDriverCore(void);

  void Start(void);
  void Stop(void);
  void WorkThread(void);
  void MessageThread(void);
  bool OnMessage(UINT message);

private:
  WptSettings _settings;
  WptHook     _hook;
  WptStatus&  _status;
  WebPagetest _webpagetest;
  WebBrowser *_browser;
  CWinPCap winpcap;
  CIpfw       _ipfw;
  bool        _exit;
  HANDLE      _work_thread;
  HANDLE      _message_thread;
  HWND        _message_window;
  TestServer  _test_server;
  CRITICAL_SECTION  cs;
  HANDLE      _testing_mutex;

  bool ConfigureIpfw(WptTest& test);
  void ResetIpfw(void);
  void Init(void);
  void FlushDNS(void);
  void ExtractZipFiles();
  bool ExtractZipFile(CString file);
};

