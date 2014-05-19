
#Definición de vectores
Sigma <- seq()
delta <- seq()
alpha <- seq()
beta <-seq()
lambda <- seq()

N = 50
dt = 1/N

p0 = 2
Sigma0 = 4
sigmau = 0.5

SigmaN = 0.2 #abs(rnorm(1, 0.2, 2))
Sigma[N] = SigmaN
alpha[N] = 0
delta[N] = 0
lambda[N] = sqrt(Sigma[N])/(sigmau*sqrt(2*dt))


for (i in N:(1)){
  beta[i] = (1-2*alpha[i]*lambda[i])/(dt*2*lambda[i]*(1-alpha[i]*lambda[i]))
  delta[i-1] = delta[i] + alpha[i]*lambda[i]^2*sigmau^2*dt
  Sigma[i-1] = Sigma[i]/(1-beta[i]*lambda[i]*dt)
  alpha[i-1] = 1/(4*lambda[i]*(1-alpha[i]*lambda[i]))
  fun <- function (x) (1-x^2*sigmau^2*dt/Sigma[i-1])*(1-alpha[i-1]*x)-0.5
  lambda[i-1] = uniroot.all(fun,c(-100,100))[2]
  }

print(Sigma0)
print(Sigma[1])

#par(mfrow=c(1,1)) 
#plot(delta); title("delta") 
#plot(alpha); title("alpha") 
#plot(beta); title("beta")
#plot(lambda); title("lambda")
plot(Sigma); title("Sigma")


  
  
  