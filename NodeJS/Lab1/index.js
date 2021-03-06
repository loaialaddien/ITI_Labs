const { Command } = require('commander');
const program = new Command();
program.version('0.0.1');
const fs = require('fs-extra');

program
    .option('-t, --tittle, <type>', 'the task tittle')
    .option('-i, --id <type>', 'the task id')
    .option('-s, --status [type]', 'the task status');

program.parse(process.argv);
const options = program.opts();
// here you're not using the commander lib, the above code is not necessary at all, you're just using it for the options part, you're mixing things from the lib, and it's confusing.
process.argv.forEach(element => {
    //although this will work, but if your user made something like node index.js add add add add, this command will be added 4 times, since the arguments add will be repeated 4 times
    switch (element) {
        case 'add':
            add(options)
            break;
        case 'list':
            list(options)
            break;
        case 'delete':
            deleteTask(options)
            break;
        case 'edit':
            editList(options)
            break;
    }
});

function add(opts) {
    fs.readFile('./to-do.json', function (err, data) {
        let json = JSON.parse(data) 
        //if the data is empty, this function will throw an error
        // JSON.parse(data || "[]") to guard against empty files
        // json is a terrible var name, also this mi
        //set the id incrementally
       // const id = json.length === 0 ? 0 : (json.length + 1);
        if (json[json.length - 1])
            id = (json[json.length - 1].id) + 1;
        else
            id = 0;
    //use map function, don't mutate 
        json.push({
            'tittle': opts.tittle,
            'id': id,
            'status': opts.status || 'to-do'
        })
        fs.writeFile("./to-do.json", JSON.stringify(json))
        //this line should be at the begining of the function. you handle the error first, because if you don't, the above functions will throw
        if (err) return console.error(err)
    })
}

function list(options) {
    //same comments as the above
    fs.readFile('./to-do.json', (err, data) => {
        let json = JSON.parse(data);
        if (options.status) {
            json = json.filter((ele) => {
                return ele.status == options.status;
            })
        }
        if (err) return console.error(err)
        console.log(json);
        return json
    })
}

function deleteTask(options) {
    fs.readFile('./to-do.json', (err, data) => {
        let json = JSON.parse(data);
        json = json.filter(ele => {
            return ele.id != options.id;
        });
        fs.writeJson('./to-do.json', json, err => {
            if (err) return console.error(err)
            console.log('the tittle has been deleted successfully!')
        })
        if (err) return console.error(err)
    })
}

function editList(options) {
    if (!options.id)
        throw "you must specify the id of the task you wanna edit"
    fs.readFile('./to-do.json', (err, data) => {
        let found = 0;
        let json = JSON.parse(data);
        //use map function instead
        json.forEach(element => {
            if (element.id == options.id) {
                if (options.status) {
                    console.log(options)
                    if (options.status == "done" || options.status == "in progress" || options.status == "to-do") {
                        element.status = options.status;
                    }
                }
                if (options.tittle) {
                    element.tittle = options.tittle;
                }
                found = 1;
            }
        });
        if (!found) throw 'the specified id does not exist'
        fs.writeJson('./to-do.json', json, err => {
            if (err) return console.error(err)
            console.log('the task info has been edited successfully!')
        })
        if (err) return console.error(err)
    })
}
