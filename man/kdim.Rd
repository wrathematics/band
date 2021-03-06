% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/02-accessors.r
\name{kdim}
\alias{kdim}
\title{kdim}
\usage{
kdim(x)
}
\arguments{
\item{x}{A band matrix.}
}
\value{
A length 2 vector, similar to \code{dim()}.
}
\description{
Get the "dimension" of the bands, i.e. the bandwidth.
}
\details{
The first digit is the width of the lower band while the second is the
width of the upper band.  For a general band matrix, these numbers can
be different.  For a symmetric matrix, they will be the same.  For a
diagonal matrix, they will both be 0.  In any case, each will be a
non-negative integer.
}
\keyword{Accessors}

