is.badval <- function(x)
{
  is.na(x) || is.nan(x) || is.infinite(x)
}

is.inty <- function(x)
{
  abs(x - round(x)) < 1e-10
}

is.zero <- function(x)
{
  abs(x) < 1e-10
}

is.negative <- function(x)
{
  x < 0
}

is.annoying <- function(x)
{
  length(x) != 1 || is.badval(x)
}

is.string <- function(x)
{
  if (!is.character(x) || is.annoying(x))
    FALSE
  else
    TRUE
}

is.char <- function(x)
{
  if (!is.string(x) || nchar(x) != 1)
    FALSE
  else
    TRUE
}



check.is.string <- function(x)
{
  if (!is.string(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be a single string"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.char <- function(x)
{
  if (!is.char(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be a single string"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.string.or.null <- function(x)
{
  if (!is.null(x))
    check.is.string(x);
  
  invisible(TRUE)
}

check.is.int <- function(x){
  if (!is.numeric(x) || is.annoying(x) || !is.inty(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be an integer"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.natnum <- function(x)
{
  if (!is.numeric(x) || is.annoying(x) || !is.inty(x) || is.negative(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be a natural number (0 or positive integer)"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.posint <- function(x)
{
  if (!is.numeric(x) || is.annoying(x) || !is.inty(x) || is.negative(x) || is.zero(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be a positive integer"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.flag <- function(x)
{
  if (!is.logical(x) || is.annoying(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be TRUE or FALSE"), call.=FALSE)
  }
  
  invisible(TRUE)
}

check.is.matrix <- function(x)
{
  if (!is.matrix(x))
  {
    nm <- deparse(substitute(x))
    stop(paste0("argument '", nm, "' must be a matrix"), call.=FALSE)
  }
  
  invisible(TRUE)
}
