//---------------------------------------------------------------------------*/
//                             Connected                                     //
//---------------------------------------------------------------------------*/
char* strdup (const char* src);
//---------------------------------------------------------------------------*/
char* strdup (const char* src)
{
  size_t len   = strlen (src);
  char* result = (char *)malloc (len + 1);

  if (result == NULL) return NULL;

  memcpy (result, src, len + 1);
  return result;
}
//---------------------------------------------------------------------------*/
//                      Constructor - Destructor                             //
//---------------------------------------------------------------------------*/
my_exception::my_exception (const char* filename, const char* func,
                            const long int line, const char* message = NULL,
                            exc_code code = ERR_UNTITLED)
{
  file_name_ = strdup (filename);
  function_  = strdup (func);
  line_      = line;

  code_      = code;
  message_   = strdup (message);
}
//---------------------------------------------------------------------------*/
my_exception::my_exception (const my_exception& except)
{
  file_name_ = strdup (except.file_name_);
  function_  = strdup (except.function_);
  line_      = except.line_;

  code_      = except.code_;
  message_   = strdup (except.message_);
}
//---------------------------------------------------------------------------*/
my_exception::my_exception(my_exception&& except)
{
  file_name_ = except.file_name_;
  function_  = except.function_;
  line_      = except.line_;

  code_      = except.code_;
  message_   = except.message_;
}
//---------------------------------------------------------------------------*/
my_exception::~my_exception(void)
{
  free (file_name_);
  free (function_);

  if (message_ != NULL) free(message_);
}
//---------------------------------------------------------------------------*/
//                            Methods                                        //
//---------------------------------------------------------------------------*/
void my_exception::where(std::ostream& os)
{
  os << " # file: "     << file_name_ << "\n"
     << " # function: " << function_  << "\n"
     << " # line: "     << line_      << "\n";
}
//---------------------------------------------------------------------------*/
void my_exception::what(std::ostream& os)
{
  if (message_ != NULL) os <<  message_          << "\n";
  else                  os << "message_ is null" << "\n";
}
//---------------------------------------------------------------------------*/
void my_exception::code(std::ostream& os)
{
  os << " # code error: " << code_ << "\n";
}
//---------------------------------------------------------------------------*/
void my_exception::info  (std::ostream& os)
{
  where (os);
  what  (os);
  code  (os);
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
