#ifndef FORMATEXCEPTION_HPP_
# define FORMATEXCEPTION_HPP_

# include <exception>

class FormatException : public std::exception
{
  virtual const char *what() const throw() {
    return "Error: bad format of command";
  }
};

#endif /* FORMATEXCEPTION_HPP_ */
