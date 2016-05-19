valid.GenBandMat <- function(object)
{
  # if (any(dim(object@Data) > object@dim))
  #   return("impossible dimensions: dimension of data larger than @dim slot")
  
  #TODO more checks...
  
  return(TRUE)
}

valid.SymBandMat <- function(object)
{
  #TODO ...
  TRUE
}
