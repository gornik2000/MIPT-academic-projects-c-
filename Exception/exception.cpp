//---------------------------------------------------------------------------*/
//                      Constructor - Destructor                             //
//---------------------------------------------------------------------------*/
my_exception::my_exception (const char* filename, const char* func,
                            const long int line, const char* message = NULL,
                            exc_code code = UNTITLED)
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

  if (message_ != NULL)
  {
    free(message_);
  }
}
//---------------------------------------------------------------------------*/
//                            Methods                                        //
//---------------------------------------------------------------------------*/
void my_exception::where(std::ostream& os)
{
  os << "file: " << file_name_ << ", function: " << function_ << ", line: "
  << line_ << std::endl;
}
//---------------------------------------------------------------------------*/
void my_exception::what(std::ostream& os)
{
  if (message_ != NULL)
  {
    os << message_ << std::endl;
  }
  else
  {
    os << "message is null" << std::endl;
  }
}
//---------------------------------------------------------------------------*/
void my_exception::code(std::ostream& os)
{
  os << "code error: " << code_ << std::endl;
}
//---------------------------------------------------------------------------*/
//                      © Gorbachev Nikita, March 2019                       //
//---------------------------------------------------------------------------*/
