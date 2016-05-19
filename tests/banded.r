library(band)

### Diagonal band
x_int <- matrix(1:100, 10, 10)
x_double <- x_int
storage.mode(x_double) <- "double"

truth <- diag(x_int)
test <- as.band(x_int, 0, 0)@Data
stopifnot(all.equal(truth, test))

truth <- as.double(truth)
test <- as.band(x_double, 0, 0)@Data
stopifnot(all.equal(truth, test))



### 
