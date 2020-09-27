const express = require('express')
const mustacheExpress = require('mustache-express')
const bodyParser = require('body-parser')

const app = express()
const port = 3000

app.set('views', `views`)
app.set('view engine', 'mustache')
app.engine('mustache', mustacheExpress())
app.use(bodyParser.urlencoded({extended: true}))

app.get('/', (req, res) => {
    res.render('index', {hello: "Enter Your Name"})
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})