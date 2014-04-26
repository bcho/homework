(function () {
    function sleep(ms) {
        var start = new Date().getTime();

        for (var i = 0; i < 1e7; i++) {
            if ((new Date().getTime() - start) > ms) {
                break;
            }
        }
    }

    var margin = {top: 20, right: 20, bottom: 30, left: 40},
        width = 1200 - margin.left - margin.right,
        height = 500 - margin.top - margin.bottom;

    var x = d3.scale.ordinal()
        .rangeRoundBands([0, width], .1);

    var y = d3.scale.linear()
        .range([height, 0]);

    var xAxis = d3.svg.axis()
        .scale(x)
        .orient('bottom');

    var yAxis = d3.svg.axis()
        .scale(y)
        .orient('left')
        .ticks(10);

    var svg = d3.select('body').append('svg')
            .attr('width', width + margin.left + margin.right)
            .attr('height', height + margin.top + margin.bottom)
        .append('g')
            .attr('transform', 'translate(' + margin.left + ',' + margin.top + ')');

    d3.xml('data.xml', 'application/xml', function(xml) {
        var snapShots = xml.documentElement.getElementsByTagName('snapshot'),
            snapShotData = valueToData(snapShots[0]);

        function valueToData(values) {
            var data = [];

            for (var i = 0; i < values.length; i++) {
                data.push(values[i]);
            }

            return data;
        }

        var drawSnapShot = function(snapShot) {
            d3.select('#chart').remove();

            var data = valueToData(snapShot.getElementsByTagName('data')[0].getElementsByTagName('value')),
                colors = valueToData(snapShot.getElementsByTagName('colors')[0].getElementsByTagName('value')),
                g = svg.append('g').attr('id', 'chart');

            x.domain(data.map(function (d, i) { return i; }));
            y.domain([0, d3.max(data, function (d) { return +d.textContent; })]);

            g.append('g')
                .attr('class', 'x axis')
                .attr('transform', 'translate(0,' + height + ')')
                .call(xAxis);

            g.append('g')
                .attr('class', 'y axis')
                .call(yAxis)
            .append('text')
                .attr('transform', 'rotate(-90)')
                .attr('y', 3)
                .attr('dy', '.71em')
                .style('text-anchor', 'end')
                .text('num');
                
            g.selectAll('.bar')
                .data(data)
            .enter().append('rect')
                .attr('class', 'bar')
                .attr('x', function (d, i) { return x(i); })
                .attr('width', x.rangeBand())
                .attr('y', function (d) { return y(+d.textContent); })
                .attr('height', function (d) {
                    return height - y(+d.textContent);
                })
                .attr('class', function (d, i) {
                    var index,
                        name,
                        class_ = ['bar'];

                    for (var j = 0; j  < colors.length; j++) {
                        index = +colors[j].attributes.index.value;
                        name = colors[j].attributes.name.value;

                        if (index === i) {
                            class_.push(name);
                        }
                    }

                    return class_.join(' ');
                })
            .append('svg:title')
                .text(function (d) { return d.textContent; });
        };

        var progress = document.querySelector('#progress');
        progress.max = snapShots.length - 1;
        progress.onchange = function () {
            drawSnapShot(snapShots[+progress.value]);
        };

        var autoDraw = function () {
            progress.value = +progress.value + 1;
            drawSnapShot(snapShots[+progress.value]);

            if (+progress.value < +progress.max) {
                window.setTimeout(autoDraw, 200);
            }
        }

        window.setTimeout(autoDraw, 200);
    });
})();
