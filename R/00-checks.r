valid.GenBandMat <- function(object)
{
  # if (any(dim(object@Data) > object@dim))
  #   return("impossible dimensions: dimension of data larger than @dim slot")
  
  #TODO more checks...
  
  return(TRUE)
}

valid.SymMat <- function(object)
{
  #TODO ...
  TRUE
}

valid.DiagMat <- function(object)
{
  # if (!all(object@dim == length(object@Data)))
  #   return("invalid dimension specification for DiagMatrix")
  
  return(TRUE)
}

valid.ZeroMat <- function(object)
{
  if (!all(object@dim > 0))
    return("invalid dimension specification for ZeroMatrix")
  
  return(TRUE)
}
