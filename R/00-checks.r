valid.GenBandMat <- function(object)
{
  # if (any(dim(object@Data) > object@dim))
  #   return("impossible dimensions: dimension of data larger than @dim slot")
  if (length(object@dim) != 2)
    return("dimension attribute must have exactly 2 numbers (nrows x ncols)")
  
  
  return(TRUE)
}

valid.SymMat <- function(object)
{
  if (length(object@dim) != 2)
    return("dimension attribute must have exactly 2 numbers (nrows x ncols)")
  if (object@dim[1L] != object@dim[2L])
    return("invalid dimension specification for SymMat")
  if (!is.char(object@triangle) || !(object@triangle %in% c('l', 'u')))
    return("'triangle' must be 'l' or 'u'")
  
  TRUE
}

valid.DiagMat <- function(object)
{
  if (length(object@dim) != 2)
    return("dimension attribute must have exactly 2 numbers (nrows x ncols)")
  if (!any(object@dim == length(object@Data)))
    return("invalid dimension specification for DiagMatrix")
  
  return(TRUE)
}

valid.ZeroMat <- function(object)
{
  if (length(object@dim) != 2)
    return("dimension attribute must have exactly 2 numbers (nrows x ncols)")
  if (!all(object@dim > 0))
    return("invalid dimension specification for ZeroMatrix")
  
  return(TRUE)
}
