valid.GenBandMat <- function(x)
{
  if (any(dim(x@Data) > x@dim))
    return("impossible dimensions: dimension of data larger than @dim slot")
  
  #TODO more checks...
  
  return(TRUE)
}

valid.SymBandMat <- function(x)
{
  #TODO ...
  TRUE
}
